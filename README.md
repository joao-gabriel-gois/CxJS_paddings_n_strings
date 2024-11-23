# JS Strings Methods / Paddings in C

After watching a [video from Augusto Galego](https://www.youtube.com/watch?v=Y97NBRSTMAk) (PT-BR) about why JS is bad, I got really shocked about the leftpad case. There was a npm package called leftpad that got unavailable and broke the web. I've checked for recent leftpad npm packages and found this one: [left-pad](https://www.npmjs.com/package/left-pad). There is even worse cases, like is-odd (literally one line of code). Based on `left-pad` README example of inputs and expected outputs, I've implemented it with 6 lines of code:

```javascript
function leftPad(string, repeat, char = ' ') {
  string = String(string);
  char = String(char);
  repeat = repeat - string.length;
  pad = '';
  for (let i = 0; i < repeat; i++) pad += char;
  return pad + string;       
}
```

A lot of people love to claim that JS ecosystem is good. I'm a TS/JS developer as well, but I think we should not endorse this bad habit with a lie. This is not a sign of a good ecosystem, at all. Six lines that would avoid several websites of going down, this is outrageous. It should make us think about how we ended up creating so much cummulative dependency hell - in cases like this, with not a single defensible reason.

___

## C Impls

Based on that, I've created this repo, just to perform some implementations as a personal "leet code" case to prove a point: If padding is easy in C, why do we need a npm package and increase our dependency chain?

Here you can find 2 implementations:

1. left, right and symmetrical pads: [string_paddings.c](string_paddings.c)
    
    a. In order to return the strings and don't change the original string, I implemented it in such a way that it is required to free after calling the padding functions. Because of that, for the topic 2 bellow, the decision was different.

2. Most common JS string methods, but in C: [string_JS_methods.c](string_JS_methods.c)

    a. As most of the JS array methods never change the original array, but return a new one, in order to do it in C, I created an allocation function. So only a writeable string is necessary for subsequent changes in the same variable and the scope in which it was allocated who's responsible to free it. You can find an example bellow:
    ```c
      // Can't change, as the original str in JS. Allocated in the Stack. ⬇
      char* mundial_lie = "Palmeiras tem mundial"; 
      // Writeable string, where we can change and free it only once after subsequent changes with different possible final sizes ⬇
      char* mundial_truth = alloc_writeable_str(mundial_lie);
      replace(&mundial_truth, "tem", "não tem");
      printf("%s\n", mundial_truth); 
      // > Palmeiras não tem mundial
      free(mundial_truth);
    ```

There was also one additional rule: I couldn't use `string.h`. Only `stdlib.h`.

## Running

You can use the `run` bash script (it uses gcc and was ran in debian based linux OS): `./run <file>.c`

## Valgrind outputs

As we are using malloc, I've ran `valgrind --leak-check=full --track-origins=yes ./bin` for `string_JS_methods.c` to check for any memory leaks. Based on its outputs, I've asked to GPT to summarize the report and its analysis was useful to fix some possible failures (some missing allocation for null character / possible invalid loop index checks). It was required, since the binary was running without any warning or errors and with the expected output. Still some points mentioned by valgrind, but the reallocation for operations that changes the string size, there is no leaking memory, as you can see by this output:

```bash
$ gcc -o bin string_JS_method.c
$ valgrind --leak-check=full ./bin 2>&1 >/dev/null | tail -n 6 | head -n 3

==337966==   total heap usage: 39 allocs, 39 frees, 5,158 bytes allocated
==337966== 
==337966== All heap blocks were freed -- no leaks are possible**
```
