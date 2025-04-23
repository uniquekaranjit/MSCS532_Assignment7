(** Statistical functions for calculating mean, median, and mode of integer lists *)

(** [mean lst] calculates the arithmetic mean of a list of integers.
    @param lst List of integers to calculate mean from
    @return Float representing the arithmetic mean
    @raise Invalid_argument if the input list is empty *)
let mean lst =
  if List.length lst = 0 then
    raise (Invalid_argument "Cannot calculate mean of empty list")
  else
    let total = List.fold_left (+) 0 lst in
    float_of_int total /. float_of_int (List.length lst)

(** [median lst] calculates the median value of a list of integers.
    For even-length lists, returns the average of the two middle values.
    @param lst List of integers to calculate median from
    @return Float representing the median value
    @raise Invalid_argument if the input list is empty *)
let median lst =
  if List.length lst = 0 then
    raise (Invalid_argument "Cannot calculate median of empty list")
  else
    let sorted = List.sort compare lst in
    let len = List.length sorted in
    if len mod 2 = 0 then
      let mid1 = List.nth sorted (len / 2 - 1) in
      let mid2 = List.nth sorted (len / 2) in
      (float_of_int (mid1 + mid2)) /. 2.0
    else
      float_of_int (List.nth sorted (len / 2))

(** [mode lst] finds the most frequently occurring values in a list.
    Returns a list of tuples containing the value and its frequency.
    @param lst List of integers to find mode from
    @return List of (value, frequency) tuples for all values that appear most frequently
    @raise Invalid_argument if the input list is empty *)
let mode lst =
  if List.length lst = 0 then
    raise (Invalid_argument "Cannot calculate mode of empty list")
  else
    let counts =
      List.fold_left
        (fun acc x ->
           if List.mem_assoc x acc then
             let old = List.assoc x acc in
             (x, old + 1) :: List.remove_assoc x acc
           else
             (x, 1) :: acc)
        [] lst
    in
    let max_count = List.fold_left (fun acc (_, c) -> max acc c) 0 counts in
    List.filter (fun (_, c) -> c = max_count) counts

(** Example usage of the statistical functions *)
let () =
  let data = [1; 2; 2; 3; 4] in
  Printf.printf "Dataset: [%s]\n" (String.concat ", " (List.map string_of_int data));
  Printf.printf "Mean: %.2f\n" (mean data);
  Printf.printf "Median: %.2f\n" (median data);
  Printf.printf "Mode: [%s]\n" 
    (String.concat "; " 
      (List.map (fun (x, _) -> string_of_int x) (mode data)))
