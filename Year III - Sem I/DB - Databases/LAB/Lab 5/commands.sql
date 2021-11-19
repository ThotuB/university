-- A
select COURSE.ID, COURSE.NAME, TEACHER.DEPARTMENT
    from TEACHER
    inner join COURSE
    on TEACHER.ID = COURSE.TEACHER_ID
    where TEACHER.NAME = 'Joe' and TEACHER.SURNAME = 'Mayor';

-- B
select STUDENT.*
    from STUDENT
    inner join SIGNUP
    on STUDENT.ID = SIGNUP.STUDENT_ID
    inner join COURSE
    on SIGNUP.COURSE_ID = COURSE.ID
    where COURSE.NAME = 'Programming' and extract(year from SIGNUP.YEAR) between '2015' and '2025';

-- C
select COURSE.*
    from COURSE
    inner join TEACHER
    on TEACHER.ID = COURSE.TEACHER_ID
    inner join DEPARTMENT
    on TEACHER.DEPARTMENT = DEPARTMENT.ID
    where DEPARTMENT.FACULTY = 'AC';

-- D
select distinct COURSE.NAME, STUDENT.DEPARTMENT
    from COURSE
    inner join SIGNUP
    on SIGNUP.COURSE_ID = COURSE.ID
    inner join STUDENT
    on STUDENT.ID = SIGNUP.STUDENT_ID
    where STUDENT.NAME = 'Ioan' and STUDENT.SURNAME = 'Popescu';

-- E
select distinct STUDENT.*
    from STUDENT
    inner join SIGNUP
    on STUDENT.ID = SIGNUP.STUDENT_ID
    inner join COURSE
    on SIGNUP.COURSE_ID = COURSE.ID
    inner join TEACHER
    on TEACHER.ID = COURSE.TEACHER_ID
    where TEACHER.NAME = 'Joe' and TEACHER.SURNAME = 'Mayor'

-- F
select COURSE.NAME, SIGNUP.YEAR, GRADE.ELP, GRADE.VALUE
    from GRADE
    inner join STUDENT
    on STUDENT.ID = GRADE.STUDENT_ID
    inner join SIGNUP
    on SIGNUP.STUDENT_ID = STUDENT.ID
    inner join COURSE
    on SIGNUP.COURSE_ID = COURSE.ID
    where STUDENT.NAME = 'Andrei' and STUDENT.SURNAME = 'Floraru';

-- G
select distinct STUDENT.NAME, STUDENT.SURNAME, COURSE.NAME, GRADE.VALUE
    from STUDENT
    left join SIGNUP
    on STUDENT.ID = SIGNUP.STUDENT_ID
    left join COURSE
    on SIGNUP.COURSE_ID = COURSE.ID
    left join GRADE
    on STUDENT.ID = GRADE.STUDENT_ID

-- H
select DEPARTMENT.NAME, STUDENT.NAME, STUDENT.SURNAME
    from DEPARTMENT
    left join STUDENT
    on STUDENT.DEPARTMENT = DEPARTMENT.ID

-- I
select STUDENT.NAME, STUDENT.SURNAME, COURSE.NAME
    from STUDENT
    full join SIGNUP
    on STUDENT.ID = SIGNUP.STUDENT_ID
    full join COURSE
    on SIGNUP.COURSE_ID = COURSE.ID