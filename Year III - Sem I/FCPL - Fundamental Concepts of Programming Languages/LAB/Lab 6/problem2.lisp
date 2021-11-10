(defun copy_file (file_in file_out)
    (let (
        (input_stream (open file_in 
            :direction :input
        ))
        (output_stream (open file_out 
            :direction :output 
            :if-exists :supersede 
            :if-does-not-exist :create
        ))
    )
        (do (
            (line (read-line input_stream nil :eof) (read-line input_stream nil :eof) )
        )(
            (eq line :eof)
        )
            (write-line line output_stream)
        )
        (close input_stream)
        (close output_stream)
    )
) 

(defvar path "Year III - Sem I/FCPL - Fundamental Concepts of Programming Languages/LAB/Lab 6/")
(defvar file1 (concatenate 'string path "input.txt"))
(defvar file2 (concatenate 'string path "output.txt"))

(copy_file file1 file2)