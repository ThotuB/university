*version 9.1 4018880225
u 55
V? 2
D? 2
R? 3
C? 4
@libraries
@analysis
.TRAN 1 0 0 0
+0 10m
+1 90m
+3 0.01m
.STMLIB Half-Wave Rectifier.stl
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
pageloc 1 0 2936 
@status
n 0 120:03:24:04:53:59;1587693239 e 
s 2832 120:04:30:14:01:20;1590836480 e 
c 120:03:24:04:53:53;1587693233
*page 1 0 970 720 iA
@ports
port 31 AGND 250 360 h
port 30 BUBBLE 110 280 h
a 1 x 3 0 10 0 hcn 100 LABEL=v1
port 29 BUBBLE 420 280 h
a 1 x 3 0 10 0 hcn 100 LABEL=vL
@parts
part 5 r 420 340 v
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 u 13 0 15 25 hln 100 VALUE=5k
a 0 x 0:13 0 0 0 hln 100 PKGREF=R1
a 0 xp 9 0 25 25 hln 100 REFDES=R1
part 3 D1N4002 200 280 h
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=DO-41
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=D1
a 0 ap 9 0 2 4 hln 100 REFDES=D1
a 0 sp 11 0 2 24 hln 100 PART=D1N4002
part 2 VSIN 110 300 h
a 0 a 0:13 0 0 0 hln 100 PKGREF=V1
a 1 u 0 0 0 0 hcn 100 VOFF=0
a 1 ap 9 0 25 10 hcn 100 REFDES=V1
a 1 u 13 13 40 20 hcn 100 FREQ=50
a 1 u 13 13 45 30 hcn 100 VAMPL=18.9
part 34 c 320 340 v
a 0 sp 0 0 0 10 hlb 100 PART=c
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=CK05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 x 0:13 0 0 0 hln 100 PKGREF=C1
a 0 xp 9 0 20 25 hln 100 REFDES=C1
a 0 u 13 0 5 30 hln 100 VALUE=22u
part 47 c 350 340 v
a 0 sp 0 0 0 10 hlb 100 PART=c
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=CK05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 u 13 0 5 30 hln 100 VALUE=22u
a 0 x 0:13 0 0 0 hln 100 PKGREF=C2
a 0 xp 9 0 20 25 hln 100 REFDES=C2
part 54 c 380 340 v
a 0 sp 0 0 0 10 hlb 100 PART=c
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=CK05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 u 13 0 5 30 hln 100 VALUE=22u
a 0 x 0:13 0 0 0 hln 100 PKGREF=C3
a 0 xp 9 0 20 25 hln 100 REFDES=C3
part 1 titleblk 970 720 h
a 1 s 13 0 350 10 hcn 100 PAGESIZE=A
a 1 s 13 0 180 60 hcn 100 PAGETITLE=
a 1 s 13 0 340 95 hrn 100 PAGECOUNT=1
a 1 s 13 0 300 95 hrn 100 PAGENO=1
@conn
w 24
a 0 up 0:33 0 0 0 hln 100 V=
s 110 280 110 300 25
s 200 280 110 280 23
a 0 up 33 0 155 279 hct 100 V=
w 17
a 0 up 0:33 0 0 0 hln 100 V=
s 420 280 420 300 18
s 230 280 320 280 22
a 0 up 33 0 290 279 hct 100 V=
s 320 280 350 280 37
s 320 310 320 280 35
s 350 280 380 280 43
s 350 310 350 280 41
s 380 280 420 280 50
s 380 310 380 280 48
w 8
a 0 up 0:33 0 0 0 hln 100 V=
s 110 340 110 360 7
s 110 360 250 360 9
a 0 up 33 0 180 359 hct 100 V=
s 420 360 420 340 11
s 250 360 320 360 15
s 320 360 350 360 40
s 320 340 320 360 38
s 350 360 380 360 46
s 350 340 350 360 44
s 380 360 420 360 53
s 380 340 380 360 51
@junction
j 200 280
+ p 3 1
+ w 24
j 110 280
+ s 30
+ w 24
j 420 340
+ p 5 1
+ w 8
j 250 360
+ s 31
+ w 8
j 110 300
+ p 2 +
+ w 24
j 110 340
+ p 2 -
+ w 8
j 420 300
+ p 5 2
+ w 17
j 230 280
+ p 3 2
+ w 17
j 420 280
+ s 29
+ w 17
j 320 310
+ p 34 2
+ w 17
j 320 280
+ w 17
+ w 17
j 320 340
+ p 34 1
+ w 8
j 320 360
+ w 8
+ w 8
j 350 280
+ w 17
+ w 17
j 350 360
+ w 8
+ w 8
j 350 310
+ p 47 2
+ w 17
j 350 340
+ p 47 1
+ w 8
j 380 280
+ w 17
+ w 17
j 380 360
+ w 8
+ w 8
j 380 310
+ p 54 2
+ w 17
j 380 340
+ p 54 1
+ w 8
@attributes
a 0 s 0:13 0 0 0 hln 100 PAGETITLE=
a 0 s 0:13 0 0 0 hln 100 PAGENO=1
a 0 s 0:13 0 0 0 hln 100 PAGESIZE=A
a 0 s 0:13 0 0 0 hln 100 PAGECOUNT=1
@graphics
