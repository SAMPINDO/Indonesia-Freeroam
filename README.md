# Relived Roleplay
[![sampctl](https://img.shields.io/badge/SAMPCTL-Indonesia--Freeroam-2f2f2f.svg?style=for-the-badge)](https://github.com/Lukman350/RRP)

## About

Indonesia Freeroam adalah gamemode SA:MP, fitur utama yang ditawarkan oleh gamemode ini adalah:

  - Gamemode yang terpisah berdasarkan module
  - Player Registration and Login system using MySQL plugin R41+
  - YSI Library 5+
  - Per player vehicle spawning and ownership
  - Other fun commands

## Modules

Gamemode ini menyediakan 3 module yaitu:

  - Player (Registration and Login)
  - PlayerVehicle (Per player vehicle spawning and ownership)
  - PlayerWorld (Per player virtual world)

Tiap module memiliki beberapa file yang dipisah sesuai fungsi:
  - Header.inc (bersisi constants dan variables)
  - Function.inc (berisi functions yang berkaitan dengan module)
  - Callback.inc (berisi hooks untuk callback default SA:MP)
  - QueryCallback.inc (berisi callback plugin MySQL)
  - Timer.inc (berisi timers yang berkaitan dengan module)
  - Dialog.inc (berisi callback dialog menggunakan easyDialog)
  - Command.inc (berisi command menggunakan YCMD)

## Dependencies

| Name | Version | URL |
| ------ | ------ | ------ |
| SA:MP MySQL Plugin | R41+ | https://github.com/pBlueG/SA-MP-MySQL/releases |
| Sscanf2 | 2.13.2 | https://github.com/Y-Less/sscanf/releases |
| Bcrypt | 3.4 | https://github.com/Sreyas-Sreelal/samp-bcrypt/releases |
| YSI | 5+ | https://github.com/pawn-lang/YSI-Includes/releases |
| easyDialog | 2.0 | https://github.com/Awsomedude/easyDialog/releases |


## Installation
Simply install to your project:
```bash
sampctl package install Lukman350/RRP
```