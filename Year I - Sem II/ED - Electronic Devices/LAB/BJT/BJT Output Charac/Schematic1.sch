*version 9.1 1791725134
u 43
Q? 2
R? 3
V? 5
? 2
@libraries
@analysis
.DC 1 1 0 0 0 0
+ 0 0 EC
+ 0 4 0
+ 0 5 12
+ 0 6 0.1
+ 1 0 EB
+ 1 4 1.6
+ 1 5 2.6
+ 1 6 1
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
pageloc 1 0 2492 
@status
n 0 120:04:25:23:13:59;1590437639 e 
s 0 120:04:26:00:02:26;1590440546 e 
c 120:04:26:01:06:14;1590444374
*page 1 0 970 720 iA
@ports
port 35 AGND 400 390 h
port 39 BUBBLE 400 270 v
a 1 x 3 0 10 0 hcn 100 LABEL=VC
@parts
part 5 VDC 260 330 h
a 0 sp 0 0 22 37 hln 100 PART=VDC
a 1 u 13 0 24 33 hcn 100 DC=1.6V
a 0 x 0:13 0 0 0 hln 100 PKGREF=EB
a 1 xp 9 0 24 7 hcn 100 REFDES=EB
part 3 r 310 310 h
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 x 0:13 0 0 0 hln 100 PKGREF=RB
a 0 xp 9 0 15 0 hln 100 REFDES=RB
a 0 u 13 0 15 25 hln 100 VALUE=100k
part 4 r 400 250 v
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 x 0:13 0 0 0 hln 100 PKGREF=RC
a 0 xp 9 0 15 0 hln 100 REFDES=RC
part 2 Q2N2222 380 310 h
a 0 sp 11 0 25 40 hln 100 PART=Q2N2222
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=TO-18
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=Q1
a 0 ap 9 0 5 5 hln 100 REFDES=Q1
part 6 VDC 490 270 h
a 0 sp 0 0 22 37 hln 100 PART=VDC
a 0 x 0:13 0 0 0 hln 100 PKGREF=EC
a 1 xp 9 0 24 7 hcn 100 REFDES=EC
a 1 u 13 0 24 33 hcn 100 DC=0V
part 1 titleblk 970 720 h
a 1 s 13 0 350 10 hcn 100 PAGESIZE=A
a 1 s 13 0 180 60 hcn 100 PAGETITLE=
a 1 s 13 0 300 95 hrn 100 PAGENO=1
a 1 s 13 0 340 95 hrn 100 PAGECOUNT=1
part 38 iMarker 400 290 h
a 0 s 0 0 0 0 hln 100 PROBEVAR=I(RC)
a 0 a 0 0 6 20 hlb 100 LABEL=1
@conn
w 14
a 0 up 0:33 0 0 0 hln 100 V=
s 260 310 260 330 15
s 310 310 260 310 13
a 0 up 33 0 285 309 hct 100 V=
w 12
a 0 up 0:33 0 0 0 hln 100 V=
s 350 310 380 310 32
a 0 up 33 0 365 309 hct 100 V=
w 10
a 0 up 0:33 0 0 0 hln 100 V=
s 400 290 400 270 9
s 400 270 400 250 40
a 0 up 33 0 402 260 hlt 100 V=
w 27
a 0 up 0:33 0 0 0 hln 100 V=
s 490 190 400 190 28
s 400 190 400 210 30
s 490 270 490 190 26
a 0 up 33 0 492 230 hlt 100 V=
w 18
a 0 up 0:33 0 0 0 hln 100 V=
s 260 370 260 390 17
s 260 390 400 390 19
a 0 up 33 0 330 389 hct 100 V=
s 400 390 490 390 25
s 400 330 400 390 23
s 490 390 490 310 21
@junction
j 260 330
+ p 5 +
+ w 14
j 260 370
+ p 5 -
+ w 18
j 400 330
+ p 2 e
+ w 18
j 400 390
+ w 18
+ w 18
j 400 210
+ p 4 2
+ w 27
j 310 310
+ p 3 1
+ w 14
j 350 310
+ p 3 2
+ w 12
j 380 310
+ p 2 b
+ w 12
j 400 390
+ s 35
+ w 18
j 400 290
+ p 2 c
+ w 10
j 400 250
+ p 4 1
+ w 10
j 400 290
+ p 38 pin1
+ p 2 c
j 400 290
+ p 38 pin1
+ w 10
j 400 270
+ s 39
+ w 10
j 490 270
+ p 6 +
+ w 27
j 490 310
+ p 6 -
+ w 18
@attributes
a 0 s 0:13 0 0 0 hln 100 PAGETITLE=
a 0 s 0:13 0 0 0 hln 100 PAGENO=1
a 0 s 0:13 0 0 0 hln 100 PAGESIZE=A
a 0 s 0:13 0 0 0 hln 100 PAGECOUNT=1
@graphics
