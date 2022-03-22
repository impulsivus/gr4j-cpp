# gr4j-cpp

C++ implementation of GR4J hydrologic rainfall-runoff model.
Currently a proof of concept project, but will be improved.
Tested using <https://gitlab.irstea.fr/HYCAR-Hydro/ExcelGR/raw/master/GR4J/GR4J_EN.xlsx> outputs.

# Dependencies

<https://github.com/gabime/spdlog> - included in the includes directory.

# Usage

gr4j.exe --precipitation pathToPrecipitationData --pet pathToPETData --discharge pathToDischargeData --parameters pathToParametersData --out RsquaredOutputFile

If you want to specify the parameters in the command line, use the following arguments:
| Argument  | Value |
| ------------- | ------------- |
|-x1|x1|
|-x2|x2|
|-x3|x3|
|-x4|x4|
|-s|s|
|-area|area|

Do not use --param with the arguments above.

Contents of --precipitation: Each line must correspond to value of that day.

Contents of --pet: Each line must correspond to value of that day.

Contents of --discharge: Each line must correspond to value of that day.

Contents of --out: Outputs the result of Rsquared method.

Contents of --param:
| Line  | Value |
| ------------- | ------------- |
| 1 | X1 Value |
| 2 | X2 value |
| 3 | X3 value |
| 4 | X4 value  |
| 5 | Area of catchment (square km)  |
| 6 | Value of S  |

# Compiling

With Visual C++ 19:

/Ox /EHsc /Yc /nologo /MD /I \includes /D UNICODE /D _UNICODE /Fo:intermediates\ GR4J.cpp FileReader.cpp /Fe: \gr4j.exe main.cpp
