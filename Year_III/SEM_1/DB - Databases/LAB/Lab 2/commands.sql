create sequence student_course_seq 
    start with 1
    increment by 1
    nocycle
    nocache
    noorder;

-- CREATE SIGNUP TABLE
create table "SIGNUP" (
    "ID" number(10, 0) default student_course_seq.nextval,
    "STUDENT_ID" varchar2(10),
    "COURSE_ID" number(4, 0),
    "YEAR" date,

    constraint "SIGNUP_PK" primary key ("ID"),
    constraint "SIGNUP_FK_STUDENT" foreign key ("STUDENT_ID") references "STUDENT" ("ID") on delete cascade,
    constraint "SIGNUP_FK_COURSE" foreign key ("COURSE_ID") references "COURSE" ("ID") on delete cascade,

    constraint "DUPLICATE_SIGNUP" unique ("STUDENT_ID", "COURSE_ID", "YEAR")
)

-- CREATE GRADE TABLE
create table "GRADE" (
    "SIGNUP_ID" number(10, 0),
    "DATE" date,
    "ELP" char(1),
    "VALUE" number(4,2),

    constraint "GRADE_FK_SIGNUP" foreign key ("SIGNUP_ID") references "SIGNUP" ("ID") on delete cascade,

    constraint "GRADE_CK_ELP" check ("ELP" in ('E', 'L', 'P')),
    constraint "GRADE_CK_VALUE" check ("VALUE" between 1 and 10)
)

-- INSERT IN DEPARTMENT
insert into "DEPARTMENT"
values (1, 'Computers', 'AC')

insert into "DEPARTMENT"
values (2, 'Electronics', 'ETcTi')

-- INSERT IN TEACHER
insert into "TEACHER"
values ('P1.100.111', 'Ion', 'Stanescu', 4200.57, 2)

insert into "TEACHER"
values ('P1.105.254', 'Joe', 'Mayor', 3895.11, 1)

-- INSERT IN STUDENT
insert into "STUDENT"
values ('LM6-10.425', 'Ioan', 'Popescu', 3, 1)

insert into "STUDENT"
values ('LM2-12.891', 'Andrei', 'Floraru', 2, 1)

insert into "STUDENT"
values ('LM8-16.112', 'Ioan', 'Popescu', 1, 2)

insert into "STUDENT"
values ('LM8-18.112', 'Razvan', 'Bratu', 4, 2)

-- INSERT IN COURSE
insert into "COURSE"
values (1, 'Electrice Engines', 'P1.100.111', 5)

insert into "COURSE"
values (2, 'Programming', 'P1.105.254', 4)

insert into "COURSE"
values (3, 'OOP', 'P1.105.254', 4)

-- INSERT IN SIGNUP
insert into "SIGNUP" ("STUDENT_ID", "COURSE_ID", "YEAR")
values ('LM6-10.425', 2, TO_DATE('2019', 'yyyy'))

insert into "SIGNUP" ("STUDENT_ID", "COURSE_ID", "YEAR")
values ('LM8-16.112', 1, TO_DATE('2021', 'yyyy'))

insert into "SIGNUP" ("STUDENT_ID", "COURSE_ID", "YEAR")
values ('LM2-12.891', 3, TO_DATE('2020', 'yyyy'))

insert into "SIGNUP" ("STUDENT_ID", "COURSE_ID", "YEAR")
values ('LM8-18.112', 1, TO_DATE('2019', 'yyyy'))

-- INSERT IN GRADE
insert into "GRADE"
values (1, CURRENT_DATE, 'E', 9)

insert into "GRADE"
values (1, CURRENT_DATE, 'L', 7)

insert into "GRADE"
values (1, CURRENT_DATE, 'L', 10)

-- DELETE FROM STUDENT
delete from "STUDENT"
where "NAME" = 'Razvan' 
    and "SURNAME" = 'Bratu' 
    and "DEPARTMENT" = 2;

-- UPDATE GRADE
update "GRADE"
set "VALUE" = "VALUE" + 1
where "VALUE" < 10
    and "ELP" = 'L'


-- JOIN STUDENT, DEPARTMENT, TEACHER, COURSE TABLES
select STUDENT.ID, COURSE.ID from STUDENT
inner join DEPARTMENT
on STUDENT.DEPARTMENT = DEPARTMENT.ID
inner join TEACHER
on TEACHER.DEPARTMENT = DEPARTMENT.ID
inner join COURSE
on COURSE.TEACHER_ID = TEACHER.ID
where STUDENT.NAME = 'Ioan'
    and STUDENT.SURNAME = 'Popescu'
    and COURSE.NAME = 'Programming'