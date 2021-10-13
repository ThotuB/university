create table "STUDENT" (
    "ID"            varchar2(10),
    "NAME"          varchar2(20),
    "SURNAME"       varchar2(20),
    "STUDY_YEAR"    number(1, 0),
    "DEPARTMENT"    number(2, 0),

    constraint "STUDENT_PK" primary key ("ID") using index enable,

    constraint "STUDY_YEAR_CK" check (1 <= STUDY_YEAR and STUDY_YEAR <= 7) enable
)