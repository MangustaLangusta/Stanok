#include <string>
#include <map>
#include <list>
#include <set>
#include <iostream>
#include <fstream>

#include "parser.h"
#include "gcodes_conf.h"



int main(){
	
	
	gcode::GCodeParser gcode_parser;
	
	if(!gcode_parser.AssignInputFile())
		return 0;

	if(!gcode_parser.AdoptGcode())
		return 0;
	
	gcode_parser.ReleaseInputFile();
	
	/*
	std::cout<<"Enter output file name"<<std::endl;
	std::string output_file_name = "";
	std::cin>>output_file_name;
	
	std::ofstream fout;
	fout.open(output_file_name + ".gcode");
	
	std::cout<<"Output file "<<output_file_name<<".gcode created"<<std::endl;
	*/

	return 0;
}


/*
	Добавлять:
	M104 - нагрев экструдера без ожидания окончания нагрева
	M109 - нагрев экструдера с ожиданием окончания нагрева
	M107 - выключить вентилятор
	M106 - установить скорость вентилятора
	M84 - Отключить питание шаговых двигателей

	Оставить без изменений:
	G0 - ускоренное перемещение
	G1 - линейная интерполяция (перемещение)
	G21 - размеры в миллиметрах
	G28 - занять исходное положение (home all axis)
	G90 - режим абсолютных координат
	G91 -  режим относительных координат (каждая следующая позиция - приращение)
	G92 - установить текущее положение оси (offset)
	
	Модифицировать:
	Txx	M06 - смена инструмента -> M109 (в зависимости от 
	
	Проверить: 
	G2, G3 - круговая интерполяция (по часовой / против часовой)
	G4 - задержка программы

	Убрать:

	M82 - режим абсолютных значений выдавливания филамента
	M9 - выключить охлаждение
	M190 - ждать нагрева стола
	M140 - установить нагрев стола без одидания
	Snnnn M03 - запуск шпинделя с определенной скоростью 
*/

/*
All codes G:
G00
G01
G03
G17
G21
G28
G40
G41
G43
G54
G80
G82
G90
G91
G98

All codes M:
M03
M06
M08
M09
M30

All params and unknown:
&
'
(
)
1
2
>
C
D
F
H
I
J
L
N
O
P
R
S
T
X
Y
Z
*/
