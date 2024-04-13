# Commands
1. cmake -B build/Debug -S.


# CMake
## Was ist CMake?
Grob gesagt ist CMake das System, das unser Projekt konfiguriert und "baut". "Baut" ist hierbei in Anführungszeichen, da es nicht den klassichen Compiler wie bspw. gcc/g++ ersetzt. CMake stellt diesem in gewissermaßen die benötigten Anweisungen bereit, damit "komplexere" Projekte mit mehreren zu kompilierenden Dateien problemlos und konsistent gebaut werden können.

## CMake Grundlagen:
```CMake
# CMakeLists.txt

cmake_minimum_required(VERSION 3.22)

project(ProjectName)
add_executable(ProjectName main.cpp)
```
Das ist eine einfach CMakeLists.txt Datei. Diese stellt im Prinzip die Anweisung wie das Projekt aufgebaut ist bereit.
1. Zuerst wird die minimal benötigte CMake Version gesetzt.
2. Dann wird das Projekt "initiert". Hier können auch andere Parameter wie bspw. die Version mitgegeben werden.
3. Zuletzt wird die ausführbare Datei hinzugefügt.

## Weitere Anweisung
CMake hat sehr, sehr viele mögliche Anweisung.
Für uns wichtig sind aber insbesondere:
```CMake
set(SOURCES
    src/main.cpp
    src/ORDNER/DATEI.cpp
)
```
Mit 'set' kann man in CMake Variablen setzen. Bei uns ist das insbesodere relevant, da so alle .cpp Dateien gesammelt der Executable "gegeben" werden können.
> Wenn ihr also eine neue Klasse erstellt, muss die .cpp Datei dieser Klasse zu den SOURCES in CMakeLists.txt hinzugefügt werden.

Header die unter src/include liegen, werden automatisch erkannt.

```
add_executable(${PROJECT_NAME} ${SOURCES})
```
So wird bei uns dann die Executable hinzugefügt. Die 'PROJECT_NAME' Variable wurde im vorhinein definiert.

## Subdirectorys
Des weiteren ist unser Projekt auch etwas aufgeteilt. Für die Libraries gibt es beispielsweiße unter 'lib/' eine eigenen CMake Datei welche so hinzugefügt wird.
```CMake
add_subdirectory(lib)
```

Das kann fürs erste jedoch ignoriert werden. 
Ich plane in Zukunft, die 'set(SOURCES)' Komponente in das 'src/' Verzeichnis auszulagern, jedoch mache ich das erst später irgendwa irgendwann.
