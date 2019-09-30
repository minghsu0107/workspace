#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
typedef struct mem {
	char member_name[45];
	struct mem *l;
	struct mem *r; 
} member;
typedef struct node {
    char club_name[45], leader_name[45];
    struct node *l;
    struct node *r;
    member *mem_root;
} club_node;
member *find_member(member *root, char *name) {
	if (root == NULL) return NULL;
	if (!strcmp(name, root->member_name))
    	return root;
    else if (strcmp(name, root->member_name) < 0) 
    	return find_member(root->l, name);
    else if (strcmp(name, root->member_name) > 0) 
    	return find_member(root->r, name);
}
club_node *find_club(club_node *root, char *cname) {
	if (root == NULL) return NULL;
    if (!strcmp(cname, root->club_name))
    	return root;
    else if (strcmp(cname, root->club_name) < 0) 
    	return find_club(root->l, cname);
    else if (strcmp(cname, root->club_name) > 0) 
    	return find_club(root->r, cname);
}
member *add_member(member *root, char *name) {
	if (root == NULL) {
        member *cur = (member*)malloc(sizeof(member));
        assert(cur != NULL);
        strcpy(cur->member_name, name);
        cur->l = cur->r = NULL;
        return cur;
    }
    if (strcmp(name, root->member_name) < 0) 
       root->l = add_member(root->l, name);
    else if (strcmp(name, root->member_name) > 0) 
       root->r = add_member(root->r, name);
    return root;
}
club_node *create(club_node *root, char *name, char *cname) {
    if (root == NULL) {
        club_node *cur = (club_node*)malloc(sizeof(club_node));
        assert(cur != NULL);
        strcpy(cur->leader_name, name);
        strcpy(cur->club_name, cname);
        cur->l = cur->r = NULL;
        cur->mem_root = NULL;
        cur->mem_root = add_member(cur->mem_root, name);
        return cur;
    }
    if (strcmp(cname, root->club_name) < 0) 
       root->l = create(root->l, name, cname);
    else if (strcmp(cname, root->club_name) > 0) 
       root->r = create(root->r, name, cname);
    return root;
}
club_node *insert(club_node *root, int type, char *name, char *cname) {
    if (type == 0)
       root = create(root, name, cname);
    else if (type == 1) {
       club_node *tmp = find_club(root, cname);
       tmp->mem_root = add_member(tmp->mem_root, name);  
    }
    return root;
}
int main() {
    int k, q, type;
    club_node *root = NULL;
    char name[45], cname[45];
    scanf("%d", &k);
    for (int i = 0; i < k; i++) {
    	scanf("%d%s%s", &type, name, cname);
        root = insert(root, type, name, cname);
    }
    scanf("%d",&q);
    while (q--) {
        scanf("%d", &type);
        if (type == 0) {
        	scanf("%s", cname);
        	club_node *tmp = find_club(root, cname);
		    if (tmp != NULL) {
		       printf("%s\n", tmp->leader_name);
		    } else {
		   	   puts("None");
		    }
        }
        else if (type == 1) {
            scanf("%s%s", name, cname);
            club_node *tmp = find_club(root, cname);
		    if (tmp == NULL) puts("-1");
		    else {
		   	   member *mem = find_member(tmp->mem_root, name);
		   	   if (mem != NULL) puts("1");
		   	   else puts("0");
		    }
        }
    }
    return 0;
}