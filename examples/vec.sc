let Vec = struct<T> {
	cap: u64;
	len: u64;
	data: *T;
};

let new = fn<T>(): Vec<T> {
	return Vec.<T>(1, 0, nil); // nil is an i64 with value = 0
};

let push in Vec<T> = fn(e: T) {
	if self.len == self.cap { self.cap *= 2; }
	self.data[self.len++] = e;
};
let pop in Vec<T> = fn() {
	if self.len == 0 {
		@panic("no element in vector");
	}
	self.data[--self.len].deinit();
};
