$txtFile = "slideshow.txt"
$folders = @(Get-Content -Path $txtFile | ForEach-Object { $_.Trim() } | Where-Object { $_ -ne "" -and (Test-Path $_) })

if ($folders.Count -eq 0) {
    exit
}

$current = Get-ItemPropertyValue "HKCU:\Control Panel\Personalization\Desktop Slideshow" "ImagesRootPath"
$index = $folders.IndexOf($current)

if ($index -ge 0 -and $index -lt ($folders.Count - 1)) {
    $nextPath = $folders[$index + 1]
} else {
    $nextPath = $folders[0]
}

if ($nextPath -eq $current) {
    exit
}

Set-ItemProperty -Path "HKCU:\Control Panel\Personalization\Desktop Slideshow" -Name "ImagesRootPath" -Value $nextPath

& .\slideshow.exe $nextPath
