let st = struct {
	i: i32;
	u: *const i8;
};

let stvar = st(5, "hi");
let comptime x = stvar.i;
let f = fn(i: i32, j: i32): i32 {
	return x;
};
inline if x {
	let a = 5;
} else {
	let b = 10;
}

let comptime n = 5 + 1.5;
n = 1 + 0.5;
let sum = 0;

inline for let comptime i = 0; i < 20; ++i {
	sum += i;
}

let vafn = fn<T>(va: ...T): i32 {
	return va[0] + va[1];
};

let vad = vafn(1, 2);

let comptime c = 'h';