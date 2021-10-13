create table "COURSE" (
    "ID"            varchar2(10),
    "TEACHER_ID"    varchar2(10),
    "CREDITS"       number(2, 0),

    constraint "COURSE_PK" primary key ("ID") using index enable
)

alter table "COURSE" add "NAME" varchar2(30)