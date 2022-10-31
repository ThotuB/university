*version 9.1 1337121002
u 97
V? 2
D? 7
R? 3
@libraries
@analysis
.TRAN 1 0 0 0
+0 0ns
+1 3ms
+3 0.01ms
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
pageloc 1 0 2139 
@status
n 0 120:03:24:22:30:13;1587756613 e 
s 2832 120:03:24:22:30:16;1587756616 e 
*page 1 0 970 720 iA
@ports
port 35 BUBBLE 120 310 h
a 1 x 3 0 10 0 hcn 100 LABEL=V1
port 33 AGND 180 370 h
port 36 BUBBLE 260 310 h
a 1 x 3 0 10 0 hcn 100 LABEL=VL
@parts
part 2 VSIN 120 320 h
a 0 a 0:13 0 0 0 hln 100 PKGREF=V1
a 1 u 0 0 0 0 hcn 100 VOFF=0
a 1 u 0 0 0 0 hcn 100 DC=
a 1 u 13 13 40 35 hcn 100 VAMPL=1.5
a 1 ap 9 0 25 15 hcn 100 REFDES=V1
a 1 u 13 13 40 25 hcn 100 FREQ=1k
part 77 D1N4002 220 320 d
a 0 sp 11 0 17 29 hln 100 PART=D1N4002
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=DO-41
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=D5
a 0 ap 9 0 17 4 hln 100 REFDES=D5
part 78 D1N4002 260 360 v
a 0 sp 11 0 17 29 hln 100 PART=D1N4002
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=DO-41
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=D6
a 0 ap 9 0 17 4 hln 100 REFDES=D6
part 6 r 160 310 h
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 x 0:13 0 0 0 hln 100 PKGREF=R
a 0 xp 9 0 15 0 hln 100 REFDES=R
a 0 u 13 0 15 25 hln 100 VALUE=1
part 1 titleblk 970 720 h
a 1 s 13 0 350 10 hcn 100 PAGESIZE=A
a 1 s 13 0 180 60 hcn 100 PAGETITLE=
a 1 s 13 0 340 95 hrn 100 PAGECOUNT=1
a 1 s 13 0 300 95 hrn 100 PAGENO=1
@conn
w 24
a 0 up 0:33 0 0 0 hln 100 V=
s 160 310 120 310 23
a 0 up 33 0 140 309 hct 100 V=
s 120 310 120 320 25
w 74
a 0 up 0:33 0 0 0 hln 100 V=
s 120 370 180 370 9
a 0 up 33 0 150 369 hct 100 V=
s 120 360 120 370 7
s 180 370 220 370 80
s 220 370 260 370 83
s 220 350 220 370 81
s 260 370 260 360 90
w 96
a 0 up 0:33 0 0 0 hln 100 V=
s 220 310 260 310 86
s 260 310 260 330 87
s 200 310 220 310 79
a 0 up 33 0 285 309 hct 100 V=
s 220 320 220 310 84
@junction
j 120 320
+ p 2 +
+ w 24
j 120 310
+ s 35
+ w 24
j 160 310
+ p 6 1
+ w 24
j 200 310
+ p 6 2
+ w 96
j 220 370
+ w 74
+ w 74
j 220 320
+ p 77 1
+ w 96
j 220 310
+ w 96
+ w 96
j 260 330
+ p 78 2
+ w 96
j 120 360
+ p 2 -
+ w 74
j 180 370
+ s 33
+ w 74
j 220 350
+ p 77 2
+ w 74
j 260 360
+ p 78 1
+ w 74
j 260 310
+ s 36
+ w 96
@attributes
a 0 s 0:13 0 0 0 hln 100 PAGETITLE=
a 0 s 0:13 0 0 0 hln 100 PAGENO=1
a 0 s 0:13 0 0 0 hln 100 PAGESIZE=A
a 0 s 0:13 0 0 0 hln 100 PAGECOUNT=1
@graphics
