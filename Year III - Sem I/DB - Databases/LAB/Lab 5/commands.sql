select COURSE.ID, COURSE.NAME, TEACHER.DEPARTMENT
    from TEACHER
    inner join COURSE
    on TEACHER.ID = COURSE.TEACHER_ID
    where TEACHER.NAME = 'Joe' and TEACHER.SURNAME = 'Mayor';

select STUDENT.*
    from STUDENT
    inner join SIGNUP
    on STUDENT.ID = SIGNUP.STUDENT_ID
    inner join COURSE
    on SIGNUP.COURSE_ID = COURSE.ID
    where COURSE.NAME = 'Programming' and SIGNUP.YEAR between '01-01-2015' and '12-31-2025';

select COURSE.*
    from COURSE
    inner join TEACHER
    on TEACHER.ID = COURSE.TEACHER_ID
    inner join DEPARTMENT
    on TEACHER.DEPARTMENT = DEPARTMENT.ID
    where DEPARTMENT.FACULTY = 'AC';

select distinct COURSE.NAME, STUDENT.DEPARTMENT
    from COURSE
    inner join SIGNUP
    on SIGNUP.COURSE_ID = COURSE.ID
    inner join STUDENT
    on STUDENT.ID = SIGNUP.STUDENT_ID
    where STUDENT.NAME = 'Ioan' and STUDENT.SURNAME = 'Popescu';

select distinct STUDENT.*
    from STUDENT
    inner join SIGNUP
    on STUDENT.ID = SIGNUP.STUDENT_ID
    inner join COURSE
    on SIGNUP.COURSE_ID = COURSE.ID
    inner join TEACHER
    on TEACHER.ID = COURSE.TEACHER_ID
    where TEACHER.NAME = 'Joe' and TEACHER.SURNAME = 'Mayor'

select COURSE.NAME, SIGNUP.YEAR, GRADE.ELP, GRADE.VALUE
    from GRADE
    inner join STUDENT
    on STUDENT.ID = GRADE.STUDENT_ID
    inner join SIGNUP
    on SIGNUP.STUDENT_ID = STUDENT.ID
    inner join COURSE
    on SIGNUP.COURSE_ID = COURSE.ID
    where STUDENT.NAME = 'Andrei' and STUDENT.SURNAME = 'Floraru';

select distinct STUDENT.NAME, STUDENT.SURNAME, COURSE.NAME, GRADE.VALUE
    from STUDENT
    left join SIGNUP
    on STUDENT.ID = SIGNUP.STUDENT_ID
    left join COURSE
    on SIGNUP.COURSE_ID = COURSE.ID
    left join GRADE
    on STUDENT.ID = GRADE.STUDENT_ID


