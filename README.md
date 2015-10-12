# PLT_MRT_ARM-RPi2

This repository contains preconfigured Eclipse projects for the MRT lecture series. The purpose of these porjects is to help students to get started with the actual coding as fast a possible. The projects are not solutions to the lecture exercises. Instead they contain a framework that allows students to simply "fill in" the proper code. If any third-party dependencies are required, these are included in the project.

## Contents

The "Templates" folder contains exercise specific project templates. A project template includes dependencies (if any) and statically linked libraries/header if they are required for the exercise. Each folder in "Templates" is an Eclipse project directory.

## Usage

### Using eGit

The suggested way of using these projects is by downloading the Templates folder using Git and opening it as a workbench (File -> Switch Workbench -> Other). 

If you are running Eclipse with the eGit plugin installed, you can check out the projects from within Eclipse. Just create a new Git Project and use this repositories clone path as an URL. 

### Importing Projects

If you are using an external tool to download these projects (Git or ZIP Archive download), you can simply use "File" -> "Import" to import the workbenches.

### Settings

These projects where created and tested under GNU/Linux (OpenSUSE 13.2). It is quite possible that you will have to adapt paths of the cross-compilation toolchain under Project -> Properties -> c/c++ Build. Make sure that the Prefix and the Path matches that of the cross-compilation framework on your system. Windows users should always use the SysGCC/bin path of their portable installation.

Also make sure that the Debugging device address corresponds to your device.