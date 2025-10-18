/**
 * Author: Ezra Furtado-Tiwari
 * Date: 2025-10-18
 * Source: folklore
 * Description: Point update, range query
 * Update segment tree at different times up to MAXN. Fill array a before building the structure.
 * Usage: Perstree t(); t.t[0] = build(0,MAXN-1);
 * Time: $O(\log(N))$
 * Status: Tested on CSES
 */
#pragma once

struct Node {
	ll v;
	Node *l, *r;
	Node() {
		v = 0;
		l = r = NULL;
	}
	Node (ll cv) {
		v = cv;
		l = r = NULL;
	}
	Node (Node* cl, Node* cr) {
		v = 0;
		if (cl != NULL) {
			v += cl->v;
		}
		if (cr != NULL) {
			v += cr->v;
		}
		l = cl, r = cr;
	}
};
struct PersTree
{
	Node* t[MAXN];
	int a[MAXN];
	PersTree() {}
	Node* build (int cl, int cr) {
		if (cl == cr) {
			return new Node(a[cl]);
		}
		int cm = (cl + cr)/2;
		return new Node(build(cl,cm), build(cm+1,cr));
	}
	Node* update (int x, int v, int cl, int cr, Node* p) {
		if (cl == cr) {
			return new Node(v);
		}
		int cm = (cl + cr)/2;
		if (x <= cm) {
			return new Node(update(x,v,cl,cm,p->l),p->r);
		} else {
			return new Node(p->l, update(x,v,cm+1,cr,p->r));
		}
	}
	ll query (int l, int r, int cl, int cr, Node* p) {
		if (cr < l || cl > r) {
			return 0;
		}
		if (l <= cl && cr <= r) {
			return p->v;
		}
		int cm = (cl + cr)/2;
		return query(l,r,cl,cm,p->l) + query(l,r,cm+1,cr,p->r);
	} 
	void upd (int p, int v, int k) {
		t[k] = update(p,v,0,MAXN-1,t[k]);
	}
	ll que (int l, int r, int k) {
		return query(l,r,0,MAXN-1,t[k]);
	}
};

