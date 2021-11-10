-- INSERT INTO STUDENT
insert into "STUDENT" ("ID", "NAME", "SURNAME", "YEAR", "DEPARTMENT")
values ('LM3-11.789', 'Petru', 'Vlad', 1, 2);

insert into "STUDENT" ("ID", "NAME", "SURNAME", "YEAR", "DEPARTMENT")
values ('LM3-11.512', 'Dorel', 'Pop', 1, 2);

insert into "STUDENT" ("ID", "NAME", "SURNAME", "YEAR", "DEPARTMENT")
values ('LM6-10.982', 'Anca', 'Dan', 1, 1);

insert into "STUDENT" ("ID", "NAME", "SURNAME", "YEAR", "DEPARTMENT")
values ('LM6-10.112', 'Ileana', 'Mustata', 1, 1);

-- INSERT INTO SIGNUP
insert into "SIGNUP" ("STUDENT_ID", "COURSE_ID", "YEAR")
values ('LM6-10.425', 3, TO_DATE('2019','yyyy'));

insert into "SIGNUP" ("STUDENT_ID", "COURSE_ID", "YEAR")
values ('LM2-12.891', 3, TO_DATE('2019','yyyy'));

insert into "SIGNUP" ("STUDENT_ID", "COURSE_ID", "YEAR")
values ('LM6-10.982', 2, TO_DATE('2019','yyyy'));

insert into "SIGNUP" ("STUDENT_ID", "COURSE_ID", "YEAR")
values ('LM6-10.982', 3, TO_DATE('2019','yyyy'));

-- SELECT FROM STUDENT
select * from "STUDENT" 
order by STUDENT.NAME, STUDENT.SURNAME

select STUDENT.ID, STUDENT.DEPARTMENT from "STUDENT"
where STUDENT.NAME like 'A%' or STUDENT.NAME like 'I%'

-- SELECT FROM TEACHER
select * from "TEACHER"
where 2000 <= TEACHER.BASE_SALARY and TEACHER.BASE_SALARY <= 3000
order by TEACHER.BASE_SALARY 

-- SELECT FROM COURSE
select COURSE.NAME, COURSE.ID from "COURSE"
where COURSE.TEACHER_ID = 'P1.105.254'
order by COURSE.NAME, COURSE.ID

-- SELECT FROM SIGNUP
select SIGNUP.STUDENT_ID from "SIGNUP"
where SIGNUP.YEAR between '01-01-2019' and '12-31-2019'
group by SIGNUP.STUDENT_ID

-- CREATE TABLE EXAM_GRADES
create table "EXAM_GRADES" as
select SIGNUP.ID, SIGNUP.YEAR from "SIGNUP"
where SIGNUP.STUDENT_ID in ('LM8-16.112', 'LM6-10.982', 'LM2-12.891')

alter table "EXAM_GRADES" add "GRADE" number(3,1) default 0
