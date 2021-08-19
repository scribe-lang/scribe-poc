let st = struct {
	i: i32;
	u: *const u8;
};

let stvar = st(5, 'h');
let x = 5;
let f = fn(i: i32, j: i32): i32 {
	return i;
};