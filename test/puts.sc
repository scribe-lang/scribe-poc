let putstr = extern[puts, "<stdio.h>"] fn(data: *const i8);

let main = fn(): i32 {
	putstr("hello world");
	return 0;
};