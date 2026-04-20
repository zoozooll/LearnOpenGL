$sourcePath = "g:\Workspaces\cpp\LearnOpenGL\android\1.getting_started\1.1.hello_window"

$modules = @(
    ":1.getting_started:1.2.hello_window_clear",
    ":2.lighting:1.colors",
    ":3.model_loading:1.model_loading"
)

function CleanName($str) {
    $result = $str -replace '\d+\.', ''
    $result = $result -replace '^\.', ''
    $result = $result -replace '\.$', ''
    return $result
}

function CleanPackageName($str) {
    $result = CleanName $str
    $result = $result -replace ':', '_'
    return $result
}

foreach ($module in $modules) {
    Write-Host "Starting module: $module" -ForegroundColor Green
    
    $moduleTrimmed = $module.TrimStart(':')
    Write-Host "Trimmed: $moduleTrimmed"
    
    $lastColonIndex = $moduleTrimmed.LastIndexOf(':')
    Write-Host "Last colon index: $lastColonIndex"
    
    $titleName = $moduleTrimmed.Substring(0, $lastColonIndex)
    $tutorialName = $moduleTrimmed.Substring($lastColonIndex + 1)
    
    Write-Host "Title: $titleName"
    Write-Host "Tutorial: $tutorialName"
    
    $titleNameClean = CleanPackageName $titleName
    $tutorialNameClean = CleanName $tutorialName
    
    Write-Host "Title clean: $titleNameClean"
    Write-Host "Tutorial clean: $tutorialNameClean"
    
    $targetPath = "g:\Workspaces\cpp\LearnOpenGL\android\$titleName\$tutorialName"
    Write-Host "Target path: $targetPath"
    
    Write-Host "Creating directory..."
    $null = New-Item -ItemType Directory -Path $targetPath -Force
    
    Write-Host "Copying files..."
    Copy-Item -Path "$sourcePath\*" -Destination $targetPath -Recurse -Force
    
    Write-Host "Module done!`n" -ForegroundColor Green
}

Write-Host "All modules processed!" -ForegroundColor Green