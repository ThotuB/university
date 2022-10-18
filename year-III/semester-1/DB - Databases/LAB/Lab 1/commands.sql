-- CREATE DEPARTMENT TABLE
create table "DEPARTMENT" (
    "ID"        number(2, 0),
    "NAME"      varchar2(20) not null,
    "FACULTY"   varchar2(5) not null,

    constraint "DEPARTMENT_PK" primary key ("ID")
)

-- CREATE STUDENT TABLE
create table "STUDENT" (
    "ID" varchar2(10),
    "NAME" varchar2(20) not null,
    "SURNAME" varchar2(20) not null,
    "STUDY_YEAR" number(1, 0),
    "DEPARTMENT" number,

    constraint "STUDENT_PK" primary key ("ID"),
    constraint "STUDENT_FK_DEPARTMENT" foreign key ("DEPARTMENT") references "DEPARTMENT"("ID") on delete cascade,

    constraint "STUDY_YEAR_CK" check (1 <= STUDY_YEAR and STUDY_YEAR <= 7)
)

-- CREATE TEACHER TABLE
create table "TEACHER" (
    "ID" varchar2(10),
    "NAME" varchar2(20) not null,
    "SURNAME" varchar2(20) not null,
    "BASE_SALARY" number(7, 2),
    "DEPARTMENT" number,

    constraint "TEACHER_PK" primary key ("ID"),
    constraint "TEACHER_FK_DEPARTMENT" foreign key ("DEPARTMENT") references "DEPARTMENT"("ID") on delete cascade,

    constraint "BASE_SALARY_CK" check (BASE_SALARY >= 0)
)

-- CREATE COURSE TABLE
create table "COURSE" (
    "ID" number(4, 0),
    "NAME" varchar2(30) not null,
    "TEACHER_ID" varchar2(10),
    "CREDITS" number(2, 0),

    constraint "COURSE_PK" primary key ("ID"),
    constraint "COURSE_FK_TEACHER" foreign key ("TEACHER_ID") references "TEACHER" ("ID") on delete cascade
)