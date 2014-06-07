/*
 * Author CHY
 * Email:sunrainchy@163.com
 *
 */
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <map>
#include <stdlib.h>
#include <time.h>
using namespace std;
#define MAX(a,b) (a>b?a:b)
#define maxn 110000
#define ws ws1
int wa[maxn],wb[maxn],wv[maxn],ws[maxn];
int cmp(int *r,int a,int b,int l)
{return r[a]==r[b]&&r[a+l]==r[b+l];}
void da(char *r,int *sa,int n,int m){
	int i,j,p,*x=wa,*y=wb,*t;
	for(i=0;i<m;i++) ws[i]=0;
	for(i=0;i<n;i++) ws[x[i]=r[i]]++;
	for(i=1;i<m;i++) ws[i]+=ws[i-1];
	for(i=n-1;i>=0;i--) sa[--ws[x[i]]]=i;
	for(j=1,p=1;p<n;j*=2,m=p){
		for(p=0,i=n-j;i<n;i++) y[p++]=i;
		for(i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j;
		for(i=0;i<n;i++) wv[i]=x[y[i]];
		for(i=0;i<m;i++) ws[i]=0;
		for(i=0;i<n;i++) ws[wv[i]]++;
		for(i=1;i<m;i++) ws[i]+=ws[i-1];
		for(i=n-1;i>=0;i--) sa[--ws[wv[i]]]=y[i];
		for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++)
			x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
	}
	return;
}
int rank[maxn],height[maxn];
void calheight(char *r,int *sa,int n){
	int i,j,k=0;
	for(i=1;i<=n;i++) rank[sa[i]]=i;//在计算height的时候顺便就把rank计算出来了，反正也要用
	for(i=0;i<n;height[rank[i++]]=k)
		for(k?k--:0,j=sa[rank[i]-1];r[i+k]==r[j+k];k++);
	return;
}
char rec[maxn];
int sa[maxn],n,ans,num,pos=0;
char sta[maxn];
map<int,int> small;
struct point{
	point *father;
	point *next[4];
}root,po[maxn];
point* insert_trie(point *root,char *name){
	if(name[0]==0)
		return root;
	if(root->next[name[0]-'1']==NULL){
		po[pos].father=root;
		root->next[name[0]-'1']=&po[pos++];

	}
	return insert_trie(root->next[name[0]-'1'],name+1);
}
point* back(point *root,int n){
	while(n--){
		root=root->father;
	}
	return root;
}
int find_ans(){
	int i,j,k,pre_len=0,diff,p;
	point *f_root=&root;;
	char ch;
	small.clear();
	memset(&root,0,sizeof(root));
	num--;//这里是需要的，因为要包括头尾部，所以这里一定要
	for(i=0;i<num;i++)
		small[height[i]]++;
	for(i=num;i<=n;i++){
		if(small[height[i-num]]==1)
			small.erase(height[i-num]);
		else small[height[i-num]]--;
		small[height[i]]++;
		diff=(small.begin())->first-pre_len;
		if(diff==0)
			continue;
		if(diff>0){	
			p=sa[i];//+1
			ch=rec[p+(small.begin()->first)];
			rec[p+(small.begin()->first)]=0;
			f_root=insert_trie(f_root,rec+p+pre_len);
			rec[p+(small.begin()->first)]=ch;
		}else{
			f_root=back(f_root,abs(diff));
		}
		pre_len=(small.begin())->first;
	}
	return 0;
}
int traverse(point *root){
	for(int i=0;i<4;i++){
		if(root->next[i]){
			sta[pos]=i+'1';
			pos++;
			sta[pos]=0;
			printf("%s\n",sta);
			traverse(root->next[i]);
			pos--;
		}
	}
	return 0;
}
int main(){
	int i,j,k;
	pos=0;
	while(scanf("%d",&num)!=EOF){
		memset(&root,0,sizeof(root));
		memset(po,0,sizeof(po));
		scanf("%s",rec);
		n=strlen(rec);
		da(rec,sa,n+1,200);//这里是n+1 因为看这个函数里面是 < n 的
		calheight(rec,sa,n);//注意这里面是 n 了因为看函数里面是 <=n 的，所以这里要注意
		for(i=0;i<=n;i++){
			printf("%d ",height[i]);
		}
		printf("\n");
		pos=0;
		find_ans();
		cout<<pos<<endl;
		pos=0;
		printf("The last result maybe very large\n");
		traverse(&root);
	}
	return 0;
}

