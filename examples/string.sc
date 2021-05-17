let io = import("std/io");
let str = import("std/str");

let main = fn() {
	let cstr = "c like string"; // type = *const u8
	let str1 = str.new("object string"); // type(struct) = str.Str
	let str2 = str1; // deep copy = calls copy() function for str1 (str1.copy())
	str2 += " added to object string"; // calls += overloaded operator with *const u8 as argument
	let str3 = str2 + str2; // calls + overloaded operator with str.Str as argument; overloads can be for multiple types
	let str4: &str.Str = str2; // makes a reference of str2 => str4
	let str5: str.Str; // all types/structs are capitalized or suffixed with "_t" (TBD); calls init() STATIC function of str.Str
	let str6: *str.Str; // pointers yay!; the init() function for a pointer will initialize it to nil;
	str6 = &str2; // assign to pointer
	str6->clear(); // pointer member function call; clear() must set the internal dynamic array to nil so that deinit() works properly
	// calls deinit() functions implicitly for all non references & non pointers, ie.: str2, str3, str4, str5
};