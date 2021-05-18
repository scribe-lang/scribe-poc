let str = @import("std/str");

let c_puts = extern[puts, "<stdio.h>"] fn(data: *const u8): i32;

let println = fn(format_str: *const u8, va: ...anytype): i32 {
	return println(str.Str(format_str), va...);
};

let println = fn(fmt_str: str.Str, va: ...anytype): i32 {
	let len = fmt_str.len();
	let j = 0;
	for let i = 0; i < fmt_str.len(); ++i {
		if fmt_str[i] == '{' {
			if i > 0 && fmt_str[i - 1] == '\\' { continue; }
			if i == fmt_str.len() - 1 { continue; }
			if fmt_str[i + 1] != '}' { continue; }
			fmt_str.erase(i);
			fmt_str.erase(i);
			if j == va.len {
				panic("arguments for format string are not enough!");
			}
			i = fmt_str.insert(i, va[j++].str()) - 1;
		}
	}
	fmt_str += '\n';
	return c_puts(fmt_str.cstr());
};