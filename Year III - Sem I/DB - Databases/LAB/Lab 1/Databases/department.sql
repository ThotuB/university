create table "DEPARTMENT" (
    "ID"        number(2, 0),
    "NAME"      varchar2(20),
    "FACULTY"   varchar2(5),

    constraint "DEPARTMENT_PK" primary key ("ID") using index enable
)