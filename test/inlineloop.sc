let putstr = extern[puts, "<stdio.h>"] fn(data: i32);
// let Range = struct {
// 	current: i32;
// 	start: i32;
// 	end: i32;
// 	iter: i32;
// 	started: i32;
// 	ended: i32;
// };

// let next in Range = fn() {
// 	if self.started == 1 {
// 		self.current += self.iter;
// 		return;
// 	}
// 	self.current = self.start;
// 	self.started = 1;
// 	return;
// };

// let has_next in Range = fn(): i1 {
// 	return self.current != self.ended;
// };

// let has_next in Range = fn(): i32 {
// 	return self.end;
// };

// let range = fn(start: i32, end: i32): i32 {
// 	let r = Range(start, start, end, 1, 0, 0);
// 	let s = r.has_next();
// 	return s;
// };

// let comptime p = range(1, 2);

// let fmt = fn(comptime f: *const u8): i32 {
// 	// let comptime len = @strlen(f);
// 	let comptime sum = 0;
// 	inline for let comptime i = 0; i < 5; ++i {
// 		sum += i;
// 	}
// 	return sum;
// };

let vafn = fn<T>(va: ...T): i32 {
	let comptime sum = 0;
	inline for let comptime i = 0; i < 5; ++i {
		sum += va[i % 3];
	}
	return sum;
};
let comptime v = vafn(5, 6, 7);

// let comptime x = fmt("hi");
// let comptime y = fmt("hi");