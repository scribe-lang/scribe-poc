let io = @import("std/io");
let mem = @import("std/mem");
let cfuncs = @import("std/cfuncs");

let String = struct {
	data: *i8;
	size: u64;
	cap: u64;
};

let new = fn(): String {
	let d = mem.malloc(:i8, 2);
	return String(d, 0, 2);
};

let deinit in String = fn() {
	if @as(:i8, self.data) == 0 { return; }
	mem.free(self.data);
	self.data = 0;
};

let cstr in String = fn(): *const i8 {
	return self.data;
};

let append in String = fn(data: *const i8) {
	let len = cfuncs.strlen(data);
	let remaining = self.cap - self.size;
	while len > remaining {
		self.cap *= 2;
		self.data = mem.realloc(self.data, self.cap);
		remaining = self.cap - self.size;
	}
	for let i = 0; i < len; ++i {
		self.data[self.size++] = data[i];
	}
	self.data[self.size] = 0;
};

let main = fn(): i32 {
	let str = new();
	str.append("hello");
	str.append(" what's up");
	io.print(str);
	str.deinit();
	return 0;
};