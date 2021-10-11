type 'a node = 
    | Null
    | Node of ('a node  * 'a * 'a node)
;;

let rec insert elem root = match root with
    | Null -> Node (Null, elem, Null)
    | Node (left, x, right) ->
        if elem < x then
            Node (insert elem left, x, right)
        else if elem > x then
            Node (left, x, insert elem right)
        else
            root
;;

let rec search elem root = match root with
    | Null -> false
    | Node (left, x, right) ->
        if elem < x then
            search elem left
        else if elem > x then
            search elem right
        else
            true

let rec preorder root = match root with
    | Null -> []
    | Node (left, x, right) ->
        [x] @ preorder left @ preorder right
;;

let rec inorder root = match root with
    | Null -> []
    | Node (left, x, right) ->
        inorder left @ [x] @ inorder right
;;

let rec postorder root = match root with
    | Null -> []
    | Node (left, x, right) ->
        postorder left @ postorder right @ [x]
;;

let root = insert 5 Null;;
let root = insert 2 root;;
let root = insert 8 root;;
let root = insert 3 root;;
let root = insert 1 root;;
let root = insert 6 root;;
let root = insert 7 root;;
let root = insert 9 root;;
let root = insert 4 root;;

Printf.printf "Search (3): %b\n" (search 3 root);;
Printf.printf "Search (7): %b\n" (search 7 root);;
Printf.printf "Search (10): %b\n" (search 10 root);;

Printf.printf "Preorder: ";;
List.iter (Printf.printf "%d ") (preorder root);
Printf.printf "\nInorder: ";;
List.iter (Printf.printf "%d ") (inorder root);
Printf.printf "\nPostorder ";;
List.iter (Printf.printf "%d ") (postorder root);
Printf.printf "\n"