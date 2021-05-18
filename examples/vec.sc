let Vec = struct<T> {
	cap: u64;
	len: u64;
	data: *T;
};

let new = fn<T>() {
	return Vec<T>(1, 0, nil);
};

let push = fn<T>(self: &Vec<T>, e: T) {
	if self.len == self.cap { self.cap *= 2; }
	self.data[self.len++] = e;
};
let pop = fn<T>(self: &Vec<T>) {
	if self.len == 0 {
		@panic("no element in vector");
	}
	self.data[--self.len].deinit();
};
