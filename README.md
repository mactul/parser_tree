# Parser_Tree

Parser_Tree is a very little library that will help to parse key/value datas.  
I build it to parse http headers.

The goal of this library is to work even if we don't have all the datas in one chunk while parsing. We can update the key and the value many times before storing them with the ptree_push method.

## Documentation

### Includes

You only have to include the "parser_tree" header.
```c
#include "parser_tree.h"
```

### Init the tree

We can create a new tree by calling this function:
```c
ParserTree* tree = ptree_init();
```

### Add a key/value to the tree

This happens in 3 times.  
First, we store the key with the `ptree_update_key` method. This function allocate and reallocate some memory for the key string.  
It can be called many times to store the complete string, but it's quicker if you work with large chunks.
```c
ptree_update_key(tree, "charact");
ptree_update_key(tree, "ers string");  // The key is now set to "characters string"
```

Then, we store the value the same way with `ptree_update_value`
```c
ptree_update_value(tree, "some d");
ptree_update_key(tree, "atas");  // The key is now set to "some datas"
```

Finally, we store this pair of values in the tree with the `ptree_push` method.
```c
ptree_push(tree);
```

### Accessing datas

We can access a data with the method `ptree_get_value`, that search in the tree in O(log(N)).
```c
const char* value = ptree_get_value(tree, "my key")
```
**Warning !** If you have to modify the string returned, copy it in a new buffer or the value will be edited in the tree.

### Realeasing the memory

Once you have finished with your tree, you have to free it with the method `ptree_free`, which takes the adress of the pointer on the tree.

```c
ptree_free(&tree);
```

### A complete example

```c
#include <stdio.h>
#include "parser_tree.h"


int main()
{
    ParserTree* tree = ptree_init();

    ptree_update_key(tree, "my key 1");
    ptree_update_value(tree, "my value 1");
    ptree_push(tree);

    ptree_update_key(tree, "my ");
    ptree_update_key(tree, "key 2");
    ptree_update_value(tree, "my val");
    ptree_update_value(tree, "ue 2");
    ptree_push(tree);

    printf("%s\n", ptree_get_value(tree, "my key 1"));

    printf("%s\n", ptree_get_value(tree, "my key 2"));

    ptree_free(&tree);

    return 0;
}
```