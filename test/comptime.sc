let add = fn(x: i32, y: i32): i32 {
	if 0 {
		return x;
	} else {
		return y;
	}
};

let i = 10;
let j = 20;

let comptime res = add(i, j);