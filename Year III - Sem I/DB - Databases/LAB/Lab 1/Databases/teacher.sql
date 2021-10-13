create table "TEACHER" (
    "ID"            varchar2(10),
    "NAME"          varchar2(20),
    "SURNAME"       varchar2(20),
    "BASE_SALARY"   number(7, 2),
    "DEPARTMENT"    number(2, 0),

    constraint "TECHER_PK" primary key ("ID") using index enable,

    constraint "BASE_SALARY_CK" check (BASE_SALARY >= 0) enable
)