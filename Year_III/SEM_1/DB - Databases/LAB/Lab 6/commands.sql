-- A
select STUDENT.NAME, STUDENT.SURNAME, STUDENT.DEPARTMENT
    from STUDENT
    inner join SIGNUP
    on STUDENT.ID = SIGNUP.STUDENT_ID
    where extract(year from SIGNUP.YEAR) = '2021'

-- B
select STUDENT.NAME, STUDENT.SURNAME, STUDENT.DEPARTMENT
    from STUDENT
    where STUDENT.ID in (
        select SIGNUP.STUDENT_ID
        from SIGNUP
        where extract(year from SIGNUP.YEAR) = '2021'
    )

-- C
select distinct COURSE.*
    from COURSE
    inner join SIGNUP
    on COURSE.ID = SIGNUP.COURSE_ID

-- D
select distinct COURSE.*
    from COURSE
    where COURSE.ID in (
        select SIGNUP.COURSE_ID
        from SIGNUP
        where extract(year from SIGNUP.YEAR) = extract(year from sysdate)
    )

-- E
select STUDENT.ID, STUDENT.NAME, STUDENT.SURNAME
    from STUDENT
    where STUDENT.ID in (
        select GRADE.STUDENT_ID
        from GRADE
        where GRADE.VALUE = 10 and (GRADE.ELP = 'L' or GRADE.ELP = 'P')
    )

-- F
select COURSE.*
    from COURSE
    where COURSE.TEACHER_ID in (
        select TEACHER.ID
        from TEACHER
        inner join DEPARTMENT
        on TEACHER.DEPARTMENT = DEPARTMENT.ID
        where DEPARTMENT.FACULTY = 'AC'
    )

-- G
create table TEMP as
select STUDENT.NAME as STUDENT_NAME, STUDENT.ID as STUDENT_ID, COURSE.NAME as COURSE_NAME, TEACHER.NAME as TEACHER_NAME, SIGNUP.YEAR as SIGNUP_YEAR, GRADE.ELP as GRADE_ELP, GRADE.VALUE as GRADE_VALUE
    from STUDENT
    inner join SIGNUP
    on STUDENT.ID = SIGNUP.STUDENT_ID
    inner join COURSE
    on SIGNUP.COURSE_ID = COURSE.ID
    inner join TEACHER
    on COURSE.TEACHER_ID = TEACHER.ID
    left join GRADE
    on STUDENT.ID = GRADE.STUDENT_ID

-- H
select STUDENT.ID as STUDENT_ID, STUDENT.NAME as STUDENT_NAME, STUDENT.SURNAME as STUDENT_SURNAME, DEPARTMENT.NAME as DEPARTMENT_NAME, COURSE.NAME as COURSE_NAME, GRADE.ELP, GRADE.VALUE
    from STUDENT
    inner join DEPARTMENT
    on STUDENT.DEPARTMENT = DEPARTMENT.ID
    inner join SIGNUP
    on STUDENT.ID = SIGNUP.STUDENT_ID
    inner join COURSE
    on SIGNUP.COURSE_ID = COURSE.ID
    inner join TEACHER
    on COURSE.TEACHER_ID = TEACHER.ID
    inner join GRADE
    on STUDENT.ID = GRADE.STUDENT_ID
    where GRADE.VALUE >= 9