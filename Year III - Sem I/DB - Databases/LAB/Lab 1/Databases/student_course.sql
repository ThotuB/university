create table "STUDENT_COURSE" (
    "STUDENT_ID"    varchar2(10),
    "COURSE_ID"     varchar2(10),

    constraint "STUDENT_COURSE_PK" primary key ("STUDENT_ID", "COURSE_ID") using index enable
)

drop table "STUDENT_COURSE"