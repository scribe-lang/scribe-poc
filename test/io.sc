let io = @import("std/io");

let s = struct {
	a: i32;
	b: i32;
};

let cstr in s = fn(): *const i8 {
	let i = self.a + self.b;
	return "null";
};

let main = fn(): i32 {
	let i = 5;
	let s1 = s(5, 1);
	io.print("hi", i, s1);
	return 0;
};