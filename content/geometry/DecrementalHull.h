/**
 * Author: Daniel Zhang, Dragonslayerintraining
 * Date: 2019
 * License: Unlicense
 * Source: http://codeforces.com/blog/entry/75929
 * Description:
\\\begin{minipage}{75mm}
Maintains a decremental convex hull with $O(\log^2 n)$ per deletion.
$O(\log n)$ is possible with fractional cascading. 
\end{minipage}
\begin{minipage}{15mm}
\vspace{-6mm}
\includegraphics[width=\textwidth]{content/geometry/ConvexHull}
\vspace{-6mm}
\end{minipage}
 * Time: O(n \log^2 n)
 * Status: not tested 
*/
#pragma once

#include "Point.h"

typedef Point<ll> P;
class LeftHull{
  vector<P> p;
  struct Node{
    int bl,br;
    int L,R;
    int lc,rc;
  };
  vector<Node> n;
  int root;
  bool isleaf(int w){
    return n[w].lc==-1&&n[w].rc==-1;
  }
  void pull(int w){
    assert(!isleaf(w));
    int l=n[w].lc,r=n[w].rc;
    ll sy=p[n[r].L].y;
    while(!isleaf(l)||!isleaf(r)){
      int a=n[l].bl,b=n[l].br,
	  c=n[r].bl,d=n[r].br;
      if(a!=b && P::cross(p[a],p[b],p[c])>0) l=n[l].lc;
      else if(c!=d && P::cross(p[b],p[c],p[d])>0) r=n[r].rc;
      else if(a==b) r=n[r].lc;
      else if(c==d) l=n[l].rc;
      else{
        ll j=P::cross(p[a],p[b],p[c]);
        ll k=P::cross(p[b],p[a],p[d]);
        assert(j+k>=0);
        if(j+k==0||j*p[d].y+k*p[c].y<sy*(j+k)) l=n[l].rc;
        else r=n[r].lc;
      }
    }
    n[w].bl=n[l].L;
    n[w].br=n[r].L;
  }
  void build(int w,int L,int R){
    n[w].L=L;
    n[w].R=R;
    if(R-L==1){
      n[w].lc=n[w].rc=-1;
      n[w].bl=n[w].br=L;
    }else{
      int M=(L+R)/2;
      n[w].lc=w+1;
      n[w].rc=w+2*(M-L);
      build(n[w].lc,L,M);
      build(n[w].rc,M,R);
      pull(w);
    }
  }
  int erase(int w,int L,int R){
    if(R<=n[w].L||L>=n[w].R) return w;
    if(L<=n[w].L&&R>=n[w].R) return -1;
    n[w].lc=erase(n[w].lc,L,R);
    n[w].rc=erase(n[w].rc,L,R);
    if(n[w].lc==-1) return n[w].rc;
    if(n[w].rc==-1) return n[w].lc;
    pull(w);
    return w;
  }
  //only works for whole hull
  void get_hull(int w,int l,int r,vi& res){
    if(isleaf(w)) res.push_back(n[w].L);
    else if(r<=n[w].bl) get_hull(n[w].lc,l,r,res);
    else if(l>=n[w].br) get_hull(n[w].rc,l,r,res);
    else{
      assert(l<=n[w].bl&&n[w].br<=r);
      get_hull(n[w].lc,l,n[w].bl,res);
      get_hull(n[w].rc,n[w].br,r,res);
    }
  }
public:
  LeftHull(const vector<P>& p):p(p),n(p.size()*2),root(0){
    build(0,0,p.size());
  }
  vi get_hull(){
    if(root==-1) return {};
    vi res;
    get_hull(root,0,p.size()-1,res);
    return res;
  }
  void erase(int L){
    root=erase(root,L,L+1);
  }
};