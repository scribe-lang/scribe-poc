let mem = @import("std/mem");

let st = struct {
	t: i32;
	s: i1;
	y: bool;
};

let main = fn(): i32 {
	let p: u64 = 5;
	let a1 = mem.malloc(:i64, p); // 8 * 5
	let a2 = mem.malloc(:st, 10); // 6 * 10
	mem.free(a1);
	mem.free(a2);
	return 0;
};