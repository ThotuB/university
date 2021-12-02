*version 9.1 1070391046
u 60
V? 2
R? 2
? 2
D? 2
@libraries
@analysis
.DC 1 0 0 0 1 1
+ 0 0 V1
+ 0 4 -1
+ 0 5 10
+ 0 6 0.01
@targets
@attributes
@translators
a 0 u 13 0 0 0 hln 100 PCBOARDS=PCB
a 0 u 13 0 0 0 hln 100 PSPICE=PSPICE
a 0 u 13 0 0 0 hln 100 XILINX=XILINX
@setup
unconnectedPins 0
connectViaLabel 0
connectViaLocalLabels 0
NoStim4ExtIFPortsWarnings 1
AutoGenStim4ExtIFPorts 1
@index
pageloc 1 0 1624 
@status
n 0 120:02:24:16:50:59;1585061459 e 
s 2832 120:02:24:16:58:00;1585061880 e 
*page 1 0 970 720 iA
@ports
port 16 agnd 430 540 h
@parts
part 3 r 450 440 u
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=R1
a 0 ap 9 0 15 0 hln 100 REFDES=R1
a 0 u 13 0 15 25 hln 100 VALUE=1k
part 21 D1N4148 490 470 d
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=DO-35
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=D1
a 0 ap 9 0 15 0 hln 100 REFDES=D1
a 0 sp 11 0 25 0 hln 100 PART=D1N4148
part 2 VDC 370 470 h
a 0 sp 0 0 22 37 hln 100 PART=VDC
a 0 a 0:13 0 0 0 hln 100 PKGREF=V1
a 1 ap 9 0 24 7 hcn 100 REFDES=V1
a 1 u 13 0 -11 18 hcn 100 DC=10V
part 1 titleblk 970 720 h
a 1 s 13 0 350 10 hcn 100 PAGESIZE=A
a 1 s 13 0 180 60 hcn 100 PAGETITLE=
a 1 s 13 0 300 95 hrn 100 PAGENO=1
a 1 s 13 0 340 95 hrn 100 PAGECOUNT=1
part 20 iMarker 490 470 h
a 0 s 0 0 0 0 hln 100 PROBEVAR=I(D1)
a 0 a 0 0 6 20 hlb 100 LABEL=1
@conn
w 22
a 0 up 0:33 0 0 0 hln 100 V=
s 370 470 370 440 4
s 370 440 410 440 34
w 29
a 0 up 0:33 0 0 0 hln 100 V=
s 490 440 450 440 30
s 490 470 490 440 36
w 59
a 0 up 0:33 0 0 0 hln 100 V=
s 490 540 490 500 14
s 430 540 490 540 17
s 370 540 430 540 12
a 0 up 33 0 400 539 hct 100 V=
s 370 510 370 540 10
@junction
j 490 470
+ p 21 1
+ p 20 pin1
j 370 470
+ p 2 +
+ w 22
j 410 440
+ p 3 2
+ w 22
j 490 470
+ p 21 1
+ w 29
j 490 470
+ p 20 pin1
+ w 29
j 450 440
+ p 3 1
+ w 29
j 430 540
+ s 16
+ w 59
j 370 510
+ p 2 -
+ w 59
j 490 500
+ p 21 2
+ w 59
@attributes
a 0 s 0:13 0 0 0 hln 100 PAGETITLE=
a 0 s 0:13 0 0 0 hln 100 PAGENO=1
a 0 s 0:13 0 0 0 hln 100 PAGESIZE=A
a 0 s 0:13 0 0 0 hln 100 PAGECOUNT=1
@graphics
