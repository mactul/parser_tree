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