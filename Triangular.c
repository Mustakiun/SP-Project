#include <stdio.h>

struct Node
{
    int node_id; // variable names
    int adj_count; //   variable names
    int adjs[10];
    int costs[10];
};

// Function to add a node to the graph
int add_node(struct Node *p, int nid, int count)
{
    int i = 0, ncount = count;

    // Search for the node in the graph
    for (i = 0; i < count; i++)
    {
        if (p[i].node_id == nid)
        {
            break;
        }
    }

    // If the node is not found, add it to the graph
    if (i == count)
    {
        p[i].node_id = nid;
        p[i].adj_count = 0;
        ncount++;
    }
    return ncount;
}

// Function to add an adjacent node to the graph
void add_adjacent(struct Node *p, int nid1, int nid2, int cost, int count)
{
    int i = 0, index;

    // Search for the node in the graph
    for (i = 0; i < count; i++)
    {
        if (p[i].node_id == nid1)
        {
            int c = p[i].adj_count;
            p[i].adjs[c] = nid2;
            p[i].costs[c] = cost;
            p[i].adj_count = c + 1;
            break;
        }
    }
}

// Function to check if a node is already added to a list
int is_added(int *list, int lcount, int nid)
{
    int i = 0;

    // Search for the node in the list
    for (i = 0; i < lcount; i++)
    {
        if (list[i] == nid)
        {
            return 1; // Node found in the list
        }
    }
    return 0; // Node not found in the list
}

// Function to find a path between two nodes in the graph
void find_path(struct Node *p, int count, int start, int end, int *list, int *clist, int lcount)
{
    int index = 0, i = 0;

    // Check if the end node is reached
    if (list[lcount - 1] == end)
    {
        int tcost = 0;
        printf("\nPath: ");
        for (i = 0; i < lcount; i++)
        {
            printf("%d ", list[i]);
            tcost += clist[i];
        }
        printf(" Cost: %d", tcost);
        return;
    }

    // Search for the start node in the graph
    for (i = 0; i < count; i++)
    {
        if (p[i].node_id == start)
        {
            index = i;
            break;
        }
    }

    // Traverse adjacent nodes
    for (i = 0; i < p[index].adj_count; i++)
    {
        int a = is_added(list, lcount, p[index].adjs[i]);
        if (a == 0)
        {
            list[lcount] = p[index].adjs[i];
            clist[lcount] = p[index].costs[i];
            lcount++;

            // Recursively find path
            find_path(p, count, p[index].adjs[i], end, list, clist, lcount);
            lcount--;
        }
    }
}

int main()
{
    struct Node nodes[50];
    int node_count = 0;
    int n1 = 0, n2 = 0, c = 0;

    // Input nodes and their connections
    while (1)
    {
        printf("Enter n1, n2, cost (-9 to exit): ");
        scanf("%d %d %d", &n1, &n2, &c);
        if (n1 == -9 || n2 == -9 || c == -9)
        {
            break;
        }
        node_count = add_node(&nodes[0], n1, node_count);
        node_count = add_node(&nodes[0], n2, node_count);

        add_adjacent(&nodes[0], n1, n2, c, node_count);
        add_adjacent(&nodes[0], n2, n1, c, node_count);
    }

    int start, end;
    printf("Enter start and end nodes: ");
    scanf("%d %d", &start, &end);
    int list[50], clist[50], lcount = 0;
    list[0] = start;
    clist[0] = 0;
    lcount = 1;

    // Find and print the path between start and end nodes
    find_path(nodes, node_count, start, end, list, clist, lcount);

    return 0;
}
