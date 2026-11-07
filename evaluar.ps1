# Ejecutor de pruebas para PG207, sin Python.
# Usa los campos entrada y salida del banco definido en el enunciado.
# Ejecutar desde PowerShell:
# powershell -NoProfile -ExecutionPolicy Bypass -File .\evaluar.ps1

$ErrorActionPreference = "Stop"
Set-Location -LiteralPath $PSScriptRoot

$ejecutable = Join-Path $PSScriptRoot "reto.exe"
if (-not (Test-Path -LiteralPath $ejecutable -PathType Leaf)) {
    throw "Falta reto.exe. Compila main.c antes de ejecutar las pruebas."
}

$carpetaResultados = Join-Path $PSScriptRoot "pruebas\obtenidos"
New-Item -ItemType Directory -Path $carpetaResultados -Force | Out-Null
$resumen = @()
$hayFallos = $false

foreach ($banco in @("publicas.json", "propias.json")) {
    $casos = Get-Content -LiteralPath $banco -Raw -Encoding UTF8 | ConvertFrom-Json
    $correctos = 0
    $cantidad = @($casos).Count
    if ($cantidad -eq 0) {
        throw "El banco $banco no contiene casos."
    }

    Write-Output $banco
    $resumen += $banco

    foreach ($caso in $casos) {
        $salida = @($caso.entrada | & $ejecutable)
        $codigo = $LASTEXITCODE
        $texto = $salida -join [Environment]::NewLine

        $archivoSalida = Join-Path $carpetaResultados ($caso.nombre + ".out")
        Set-Content -LiteralPath $archivoSalida -Value $texto -Encoding ASCII

        $actual = ($texto -replace '\s+', ' ').Trim()
        $esperado = ($caso.salida -replace '\s+', ' ').Trim()
        $pasa = ($codigo -eq 0) -and ($actual -ceq $esperado)

        if ($pasa) {
            $correctos++
            $estado = "OK"
        } else {
            $hayFallos = $true
            $estado = "FALLO"
        }

        $linea = "$($caso.nombre): $estado"
        Write-Output $linea
        $resumen += $linea
    }

    $linea = "Casos correctos: $correctos / $cantidad"
    Write-Output $linea
    Write-Output ""
    $resumen += $linea
    $resumen += ""
}

Set-Content -LiteralPath "pruebas\resultado_final.txt" -Value $resumen -Encoding ASCII

if ($hayFallos) {
    exit 1
}
exit 0

