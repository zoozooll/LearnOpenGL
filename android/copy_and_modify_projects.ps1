$sourcePath = "g:\Workspaces\cpp\LearnOpenGL\android\1.getting_started\1.1.hello_window"
$logPath = "g:\Workspaces\cpp\LearnOpenGL\android\copy_log.txt"

# Clear log file
if (Test-Path $logPath) {
    Remove-Item $logPath -Force
}

$modules = @(
    ":1.getting_started:1.2.hello_window_clear",
    ":1.getting_started:2.1.hello_triangle",
    ":2.lighting:1.colors",
    ":3.model_loading:1.model_loading",
    ":4.advanced_opengl:1.1.depth_testing",
    ":8.guest:2020:oit"
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

function Log($message) {
    Write-Host $message
    Add-Content -Path $logPath -Value $message
}

Log "Starting script..."
Log "Source path: $sourcePath"
Log "Modules count: $($modules.Count)"

foreach ($module in $modules) {
    Log "`nProcessing: $module"
    
    $moduleTrimmed = $module.TrimStart(':')
    $lastColonIndex = $moduleTrimmed.LastIndexOf(':')
    $titleName = $moduleTrimmed.Substring(0, $lastColonIndex)
    $tutorialName = $moduleTrimmed.Substring($lastColonIndex + 1)
    
    $titleNameClean = CleanPackageName $titleName
    $tutorialNameClean = CleanName $tutorialName
    
    $targetPath = "g:\Workspaces\cpp\LearnOpenGL\android\$titleName\$tutorialName"
    
    Log "  Target: $targetPath"
    Log "  ApplicationId: com.example.learnopengl.$titleNameClean.$tutorialNameClean"
    
    # Create directory if it doesn't exist
    if (-not (Test-Path $targetPath)) {
        New-Item -ItemType Directory -Path $targetPath -Force | Out-Null
        Log "  Created directory"
    }
    
    # Copy files
    Copy-Item -Path "$sourcePath\*" -Destination $targetPath -Recurse -Force
    Log "  Copied files"
    
    # Update build.gradle.kts
    $buildGradlePath = "$targetPath\build.gradle.kts"
    $content = Get-Content $buildGradlePath -Raw
    $content = $content -replace 'applicationId = "com\.example\.learnopengl\.[^"]+"', "applicationId = `"com.example.learnopengl.$titleNameClean.$tutorialNameClean`""
    [System.IO.File]::WriteAllText($buildGradlePath, $content)
    Log "  Updated build.gradle.kts"
    
    # Update CMakeLists.txt
    $cmakeListsPath = "$targetPath\src\main\cpp\CMakeLists.txt"
    $content = Get-Content $cmakeListsPath -Raw
    $content = $content -replace 'project\("hello_window"\)', "project(`"$tutorialNameClean`")"
    $content = $content -replace 'set\(LEARN_OPENGL_TITLE "[^"]+"\)', "set(LEARN_OPENGL_TITLE `"$titleName`")"
    $content = $content -replace 'set\(LEARN_OPENGL_TUTORIAL "[^"]+"\)', "set(LEARN_OPENGL_TUTORIAL `"$tutorialName`")"
    $content = $content -replace 'add_library\(hello_window', "add_library($tutorialNameClean"
    $content = $content -replace 'target_link_libraries\(hello_window', "target_link_libraries($tutorialNameClean"
    [System.IO.File]::WriteAllText($cmakeListsPath, $content)
    Log "  Updated CMakeLists.txt"
    
    # Update MyGLRenderer.kt
    $rendererPath = "$targetPath\src\main\java\com\example\learnopengl\MyGLRenderer.kt"
    $content = Get-Content $rendererPath -Raw
    $content = $content -replace 'System\.loadLibrary\("hello_window"\)', "System.loadLibrary(`"$tutorialNameClean`")"
    [System.IO.File]::WriteAllText($rendererPath, $content)
    Log "  Updated MyGLRenderer.kt"
    
    # Update strings.xml
    $stringsPath = "$targetPath\src\main\res\values\strings.xml"
    $content = Get-Content $stringsPath -Raw
    $content = $content -replace '<string name="app_name">[^<]+</string>', "<string name=`"app_name`">$tutorialName</string>"
    [System.IO.File]::WriteAllText($stringsPath, $content)
    Log "  Updated strings.xml"
    
    Log "  Done!"
}

Log "`nAll modules processed successfully!"