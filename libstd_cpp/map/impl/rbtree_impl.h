// -*- C++ -*-
// HeXu's
// 2013 Nov

#ifndef HX_RBTREE_IMPL_H
#define HX_RBTREE_IMPL_H

#ifdef __cplusplus
#include <cstddef>
#include <cassert>
#else // ! __cplusplus
#include <stddef.h>
#include <stdbool.h>
#include <assert.h>
#endif // __cplusplus

#include "bintree_impl.h"

namespace Hx {
namespace detail {

/**
 * Red black tree node
 */
typedef struct rbtree_node_t: public bintree_node_t {
	struct color_t {
		enum {
			red = 0,
			black = 1,
		};
	};

	int color;
} rbtree_node_t;

/**
 * get node's color
 */
inline
int rbtree_get_color(const bintree_node_t *node)
{
	if (node == NULL)
		return rbtree_node_t::color_t::black;
	else
		return static_cast<const rbtree_node_t *>(node)->color;
}

/**
 * test if node color is red
 */
inline 
bool rbtree_is_red(const bintree_node_t *node)
{
	return (rbtree_get_color(node) == rbtree_node_t::color_t::red);
}

/**
 * test if node color is black
 */
inline
bool rbtree_is_black(const bintree_node_t *node)
{
	return (rbtree_get_color(node) == rbtree_node_t::color_t::black);
}

/**
 * set node's color
 */
inline
void rbtree_set_color(bintree_node_t *node, int color)
{
	assert(color == rbtree_node_t::color_t::red || 
		color == rbtree_node_t::color_t::black);
	static_cast<rbtree_node_t *>(node)->color = color;
}

/**
 * set node color red
 */
inline 
void rbtree_set_red(bintree_node_t *node)
{
	rbtree_set_color(node, rbtree_node_t::color_t::red);
}

/**
 * set node color black
 */
inline 
void rbtree_set_black(bintree_node_t *node)
{
	rbtree_set_color(node, rbtree_node_t::color_t::black);
}

/**
 * copy node's color
 */
inline
void rbtree_copy_color(bintree_node_t *dst, const bintree_node_t *src)
{
	rbtree_set_color(dst, rbtree_get_color(src));
}

/**
 * Restore the red-black properties after insert
 * <> -> RED
 * [] -> BLACK
 * Case 1)
 *                   [11]
 *                  /    \
 *                /        \
 *              <2>        [14]
 *             /   \          \
 *            /     \          \
 *          [1]     [7]        <15>
 *                  / \
 *                <5> <8> <-keep
 *                /
 *       viol-> <4>
 *                    ||
 *                    \/
 * case 2)
 *                   [11]
 *                  /    \
 *                /        \
 *              <2>        [14] <-keep
 *             /   \          \
 *            /     \          \
 *          [1]     <7> <-viol <15>
 *                  / \
 *                [5] [8]
 *                /
 *              <4>
 *                    ||
 *                    \/
 * case 3)
 *                   [11]
 *                  /    \
 *                /        \
 *              <7>        [14] <-keep
 *             /   \          \
 *            /     \          \
 *   viol-> <2>     [8]        <15>
 *         /   \
 *       [1]   [5] 
 *             /
 *            <4>
 *                    ||
 *                    \/
 *
 *                    [7]
 *                   /   \
 *                 /       \
 *        viol-> <2>       <11> 
 *              /   \      /  \
 *             /     \    /    \
 *           [1]    [5]  [8]   [14]
 *                  /            \
 *                <4>           <15>
 */
inline
void rbtree_insert_fixup(bintree_t *tree, bintree_node_t *viol) 
{
	// the violation node of the red-black properties
	bintree_node_t *keep = NULL;	// uncle node of violation node
	while (rbtree_is_red(viol->parent)) {
		if (viol->parent == viol->parent->parent->left) {
		 	keep = viol->parent->parent->right;
			if (rbtree_is_red(keep)) {	// Case 1
				rbtree_set_black(viol->parent);
				rbtree_set_black(keep);
				rbtree_set_red(viol->parent->parent);
				viol = viol->parent->parent;
			} else {
				if (viol == viol->parent->right) {	// Case 2
					viol = viol->parent;
					bintree_left_rotate(tree, viol);
				}
				// Case 3
				rbtree_set_black(viol->parent);
				rbtree_set_red(viol->parent->parent);
				bintree_right_rotate(tree, viol->parent->parent);
			}
		} else {
		 	keep = viol->parent->parent->left;
			if (rbtree_is_red(keep)) {	// Case 1
				rbtree_set_black(viol->parent);
				rbtree_set_black(keep);
				rbtree_set_red(viol->parent->parent);
				viol = viol->parent->parent;
			} else {
				if (viol == viol->parent->left) {	// Case 2
					viol = viol->parent;
					bintree_right_rotate(tree, viol);
				}
				// Case 3
				rbtree_set_black(viol->parent);
				rbtree_set_red(viol->parent->parent);
				bintree_left_rotate(tree, viol->parent->parent);
			}
		}
	}
	rbtree_set_black(tree->root);
}

/**
 * Restore the red-black properties after remove
 * <> -> RED
 * [] -> BLACK
 * Case 1)
 *                q                                 q
 *                |                                 |
 *               [D]                               [H]
 *              /   \                             /   \
 *            /       \           =====>        /       \
 * viol-> [[B]]        <H> <-keep            <D>         [J]
 *        /   \       /   \                 /   \       /   \
 *       A     C    [F]   [J]    viol-> [[B]]   [F]    I     K   
 *                  / \   / \            / \    / \
 *                 E   G I   K          A   C  E   G   
 * # exchange the color of D with H
 * # left rotate D
 * # goto Case 2|3|4
 *
 * Case 2)
 *                q                             q
 *                |                             |
 *                D                      viol-> D
 *              /   \                         /   \
 *            /       \        =====>       /       \
 * viol-> [[B]]        [H] <-keep        [B]         <H>
 *        /   \       /   \             /   \       /   \
 *       A     C    [F]   [J]          A     C    [F]   [J]
 *                  / \   / \                     / \   / \
 *                 E   G I   K                   E   G I   K 
 * # set H's color RED                                                      
 * # move up viol
 * # continue loop
 *                                                        
 * Case 3)
 *                q                                q
 *                |                                |
 *                D                                D
 *              /   \                            /   \
 *            /       \        =====>          /       \
 * viol-> [[B]]        [H] <-keep   viol-> [[B]]        [F] 
 *        /   \       /   \                /   \       /   \
 *       A     C    <F>   [J]             A     C     E    <H>
 *                  / \   / \                             /   \
 *                 E   G I   K                           G    [J]
 *                                                            / \
 *                                                           I   K
 * # exchange the color of F with H
 * # right rotate H
 * # goto Case 4
 *
 * Case 4)
 *                q                             q
 *                |                             |
 *                D                             H
 *              /   \                         /   \
 *            /       \        =====>       /       \
 * viol-> [[B]]        [H] <-keep        [D]         [J]
 *        /   \       /   \             /   \        / \
 *       A     C     F    <J>         [B]    F      I   K   
 *                  / \   / \         / \   / \
 *                 E   G I   K       A   C E   G 
 * # exchange the color of D with H
 * # set J's color BLACK
 * # left rotate D 
 * # and break loop
 *
 * Case 1')
 *               q                          q              
 *               |                          |              
 *              [H]                        [D]             
 *             /   \                      /   \
 *           /       \      ======>     /       \
 * keep-> <D>        [[J]] <-viol     [B]        <H> 
 *       /   \       /   \           /   \      /   \
 *     [B]   [F]    I     K         A     C   [F]  [[J]] <-viol    
 *     / \   / \                              / \   / \
 *    A   C E   G                            E   G I   K 
 * # exchange the color of D with H
 * # right rotate H
 * # goto Case 2|3|4
 *
 * Case 2')
 *               q                            q                 
 *               |                            |                 
 *               H                            H <- viol               
 *             /   \                        /   \
 *           /       \      ======>       /       \
 * keep-> [D]        [[J]] <-viol       <D>       [J]
 *       /   \       /   \             /   \     /   \
 *     [B]   [F]    I     K          [B]   [F]  I     K        
 *     / \   / \                     / \   / \
 *    A   C E   G                   A   C E   G                  
 * # set D's color RED                                                      
 * # move up viol
 * # continue loop
 * 
 * Case 3')
 *               q                                q                 
 *               |                                |                 
 *               H                                H 
 *             /   \                            /   \
 *           /       \         ======>        /       \
 * keep-> [D]        [[J]] <-viol          [F]       [[J]] <-viol
 *       /   \       /   \                /   \      /   \
 *     [B]   <F>    I     K             <D>     G   I     K        
 *     / \   / \                       /   \
 *    A   C E   G                    [B]    E                   
 *                                   / \
 *                                  A   C
 * # exchange the color of D with F
 * # left rotate D
 * # goto Case 4'
 *
 * Case 4')
 *               q                          q              
 *               |                          |              
 *               H                          D             
 *             /   \                      /   \
 *           /       \      ======>     /       \
 * keep-> [D]        [[J]] <-viol     [B]       [H] 
 *       /   \       /   \           /   \     /   \
 *     <B>    F     I     K         A     C   F    [J]
 *     / \   / \                             / \   / \
 *    A   C E   G                           E   G I   K 
 * # exchange the color of D with H
 * # set B's color BLACK
 * # right rotate H 
 * # and break loop
 *
 */
inline
void rbtree_remove_fixup(bintree_t *tree, bintree_node_t *viol)
{
	bintree_node_t *keep = NULL;	// keep the brother node of viol
	while ((viol != tree->root) && rbtree_is_black(viol)) {
		if (viol == viol->parent->left) {
			keep = viol->parent->right;	// brother node of viol
			if (rbtree_is_red(keep)) {	// Case 1
				rbtree_set_black(keep);
				rbtree_set_red(viol->parent);
				bintree_left_rotate(tree, viol->parent);
				keep = viol->parent->right;
			}
			if (rbtree_is_black(keep->left) && rbtree_is_black(keep->right)) {	// Case 2
				rbtree_set_red(keep);
				viol = viol->parent;
			} else {
				if (rbtree_is_black(keep->right)) {	// Case 3
					rbtree_set_black(keep->left);
					rbtree_set_red(keep);
					bintree_right_rotate(tree, keep);
					keep = viol->parent->right;
				}
				rbtree_copy_color(keep, viol->parent);	// Case 4
				rbtree_set_black(viol->parent);
				rbtree_set_black(keep->right);
				bintree_left_rotate(tree, viol->parent);
				viol = tree->root;
			}
		} else {	// same as then clause with "right" and "left" exchanged
			keep = viol->parent->left;	// brother node of viol
			if (rbtree_is_red(keep)) {	// Case 1'
				rbtree_set_black(keep);
				rbtree_set_red(viol->parent);
				bintree_right_rotate(tree, viol->parent);
			}
			if (rbtree_is_black(keep->left) && rbtree_is_black(keep->right)) {	// Case 2'
				rbtree_set_red(keep);
				viol = viol->parent;
			} else {
				if (rbtree_is_black(keep->left)) {	// Case 3
					rbtree_set_black(keep->right);
					rbtree_set_red(keep);
					bintree_left_rotate(tree, keep);
					keep = viol->parent->left;
				}
				rbtree_copy_color(keep, viol->parent);	// Case 4
				rbtree_set_black(viol->parent);
				rbtree_set_black(keep->left);
				bintree_right_rotate(tree, viol->parent);
				viol = tree->root;
			}
		}
	}
	rbtree_set_black(viol);
}

/**
 * remove node from red black tree 
 * Case 1)
 *        q             q
 *        |             |
 * node-> A    =====>   B
 *       / \           / \
 *     NIL  B 
 *         / \
 *
 * Case 2)
 *          q             q
 *          |             |
 *   node-> B    =====>   A
 *         / \           / \
 *        A  NIL
 *       / \
 *
 * Case 3)
 *           q                       q
 *           |                       |
 *    node-> B                       C <-keep
 *         /   \       =====>      /   \
 *       /       \               /       \
 *      A         C <-keep      A         D 
 *    /   \     /   \         /   \     /   \
 *            NIL    D
 *                  / \
 *
 * Case 4)
 *         q                   q                      q
 *         |                   |                      |
 *  node-> B            node-> B                      C <-keep
 *       /   \    =====>     /            =====>    /   \
 *     /       \           /        C <-keep      /       \
 *    A         E         A       /   \          A         E
 *  /   \     /   \     /   \   NIL    E       /   \     /   \
 *           C <-keep                /   \              D
 *          / \                     D                  / \
 *        NIL  D                   / \
 *            / \
 */
inline
void rbtree_remove(bintree_t *tree, bintree_node_t *node)
{
	rbtree_node_t placeholder;
	bintree_node_t *nil = &placeholder;
	nil->parent = nil->left = nil->right = NULL;
	rbtree_set_black(nil);
	
	bintree_node_t *viol;
	bintree_node_t *keep = node;
	int keep_color = rbtree_get_color(keep);
	if (node->left == NULL) {	// case 1: left substree is NIL
		if (node->right == NULL) {
			node->right = nil;
			nil->parent = node;
		}
		viol = node->right;
		bintree_transplant(tree, node, node->right);
	} else if (node->right == NULL) {	// case 2: right substree is NIL
		viol = node->left;
		bintree_transplant(tree, node, node->left);
	} else {
		keep = bintree_minimum(node->right);
		keep_color = rbtree_get_color(keep);
		if (keep->right == NULL) {
			keep->right = nil;
			nil->parent = keep;
		}
		viol = keep->right;
		if (keep->parent != node) { // case 4
			bintree_transplant(tree, keep, keep->right);
			keep->right = node->right;
			keep->right->parent = keep;
		} 
		bintree_transplant(tree, node, keep); // case 3
		keep->left = node->left;
		keep->left->parent = keep;
		rbtree_copy_color(keep, node);
	}
	if (keep_color == rbtree_node_t::color_t::black) {
		rbtree_remove_fixup(tree, viol);
	}
	if (viol == nil) {
		bintree_remove(tree, nil);
	}
}

#ifdef __cplusplus
/**
 * insert node into this red black tree
 */
template <typename BinaryPredicate, typename UnaryFunction>
void rbtree_insert(bintree_t *tree, bintree_node_t *node, 
	BinaryPredicate less, UnaryFunction get_key, bintree_node_t *hint = NULL)
{
	bintree_insert(tree, node, less, get_key, hint); 
	rbtree_set_red(node);
	rbtree_insert_fixup(tree, node);
}
#endif // __cplusplus

#ifdef __cplusplus
} // namespace detail
} // namespace Hx
#endif // __cplusplus

#endif // HX_RBTREE_IMPL_H
