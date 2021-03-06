let st = struct {
	i: i32;
	u: *const i8;
};

let stvar = st(5, "hi");
let comptime x = stvar.i;
let f = fn(i: i32, j: i32): i32 {
	inline if x {
		return i;
	} else {
		return j;
	}
};

let comptime n = 5 + 1.5;

let vafn = fn<T>(va: ...T): i32 {
	let sum = 0;
	inline for let comptime i = 0; i < 20; ++i {
		sum += i;
	}
	return va[0] + va[1] + sum;
};

let comptime vad = vafn(1, 2);

let comptime c = 'h';