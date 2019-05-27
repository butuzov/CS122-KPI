#include "app.cpp"
#include "binary-tree.cpp"
#include "gtest/gtest.h"

// Tree Vector Initialization Test
TEST( BinaryTree, TreeInitWithVector ) {
    BinaryTree<int> Tree( std::vector<int> {2,1,3,4} );
    ASSERT_EQ( Tree.size(),  4 );
}

// Tree - Left Leaf Insert
TEST( BinaryTree, TreeInsertLeft ) {
    BinaryTree<int> Tree( std::vector<int> {2,1} ); 
    ASSERT_EQ(1, Tree.value( ( Tree.root() )->left ) );
}

// Tree - Right Leaf Insert
TEST( BinaryTree, TreeInsertRight ) {
    BinaryTree<int> Tree( std::vector<int> {1,2} ); 
    ASSERT_EQ(2, Tree.value( ( Tree.root() )->right ) );
}

/**
 *  Traversals 
 * - Pre Order
 * - In Order (Ascending)
 * - Post ORder 
 * - Descending Order
 **/

// Test Tree Traversal in Pre Order mode.
TEST( BinaryTree, Traversal_PreOrder ) {
    BinaryTree<int> Tree( std::vector<int> {4,2,6,1,3,5,7});
    ASSERT_STREQ( "{4,2,1,3,6,5,7}", (Tree.preorder()).c_str() );
} 

// Test Tree Traversal in In Order mode.
TEST( BinaryTree, Traversal_InOrder ) {
    BinaryTree<int> Tree( std::vector<int> {4,2,6,1,3,5,7} );
    ASSERT_STREQ( "{1,2,3,4,5,6,7}", (Tree.inorder()).c_str() );
}

// Test Tree Traversal in Post Order mode.
TEST( BinaryTree, Traversal_PostOrder ) {
    BinaryTree<int> Tree( std::vector<int> {4,2,6,1,3,5,7} );
    ASSERT_STREQ( "{1,3,2,5,7,6,4}", (Tree.postorder()).c_str() );
} 

// Test Tree Traversal in Descending Order mode.
TEST( BinaryTree, Traversal_DescendingOrder ) {
    BinaryTree<int> Tree( std::vector<int> {4,2,6,1,3,5,7} );
    ASSERT_STREQ( "{7,6,5,4,3,2,1}", (Tree.descorder()).c_str() );
}

/**
 * Rotation Tests
 * 
 * - Roation Right
 * - Rotation Left
 * - Rotation Left Right 
 * - ROtation Right Left 
 **/

TEST(BinaryTree, Rotation_Left ) {
    BinaryTree<int> Tree( std::vector<int> {1,3,2,4} );
    Tree.rotate_left(Tree.root());
    ASSERT_STREQ( "{3,1,2,4}", (Tree.preorder()).c_str() );
}

TEST(BinaryTree, Rotation_Right ) {
    BinaryTree<int> Tree( std::vector<int> {4,2,1,3} );
    Tree.rotate_right(Tree.root());
    ASSERT_STREQ( "{2,1,4,3}", (Tree.preorder()).c_str() );
}

TEST(BinaryTree, Rotation_Right_Left_Root ) {
    BinaryTree<int> Tree( std::vector<int> {3,1,2} );
    Tree.rotate_right_left(Tree.root());
    ASSERT_STREQ( "{2,1,3}", (Tree.preorder()).c_str() );
}

TEST(BinaryTree, Rotation_Left_Right_Root ) {
    BinaryTree<int> Tree( std::vector<int> {1,3,2} );
    Tree.rotate_left_right(Tree.root());
    ASSERT_STREQ( "{2,1,3}", (Tree.preorder()).c_str() );
}


/**
 *  Testing Node Delition
 **/

// Case 2. This is Terminal Node. 
TEST(BinaryTree, Delete_Terminal_Node){
    BinaryTree<int> Tree( std::vector<int> {2,3,1});
    Tree.remove(Tree.find(1));
    ASSERT_STREQ( "{2,3}", (Tree.preorder()).c_str() );
}

// // Case 2. This is Terminal Node. Root.
TEST(BinaryTree, Delete_Terminal_Node_Root){
    BinaryTree<int> Tree( std::vector<int> {1});
    Tree.remove(Tree.find(1));
    ASSERT_STREQ( "{}", (Tree.preorder()).c_str() );
}

// Case 3. Scenario 1. Root Node.
// Removing non-terminal node that doesn't have right child.
TEST(BinaryTree, Delete_Root_No_Right_Child){
    BinaryTree<int> Tree( std::vector<int> {4,2,1,3});
    Tree.remove(Tree.find(4));
    ASSERT_STREQ( "{2,1,3}", (Tree.preorder()).c_str() );
}

// Case 3. Scenario 1. Child node (Right).
// Removing non-terminal node that doesn't have right child.
TEST(BinaryTree, Delete_Non_Terminal_No_Right_Child_Is_Right){
    BinaryTree<int> Tree( std::vector<int> {50,25,75,65,15});
    Tree.remove(Tree.find(75));
    ASSERT_STREQ( "{50,25,15,65}", (Tree.preorder()).c_str() );
}

// Case 3. Scenario 1. Child node (Left).
// Removing non-terminal node that doesn't have right child.
TEST(BinaryTree, Delete_Non_Terminal_No_Right_Child_Is_Left){
    BinaryTree<int> Tree( std::vector<int> {50,25,75,65,15});
    Tree.remove(Tree.find(25));
    ASSERT_STREQ( "{50,15,75,65}", (Tree.preorder()).c_str() );
}

// Case 3. Scenario 2. Child Node.
// Removing non-terminal right node that has no left child.
TEST(BinaryTree, Delete_Non_Terminal_Has_Right_Child_With_No_Left_Child){
    BinaryTree<int> Tree( std::vector<int> {50,25,75,85,95});
    Tree.remove(Tree.find(75));
    ASSERT_STREQ( "{50,25,85,95}", (Tree.preorder()).c_str() );
}

// Case 3. Scenario 2. Root.
// Removing non-terminal right node that has no left child.
TEST(BinaryTree, Delete_Root_Has_Right_Child_With_No_Right_Child){
    BinaryTree<int> Tree( std::vector<int> {50,25,75,85,95});
    Tree.remove(Tree.find(50));
    ASSERT_STREQ( "{75,25,85,95}", (Tree.preorder()).c_str() );
}

// Case 3. Scenario 2. Child node has both children.
// Removing non-terminal right node that has no left child.
TEST(BinaryTree, Delete_Non_Terminal_Has_Both_Children_But_Right_With_No_Left_Child){
    BinaryTree<int> Tree( std::vector<int> {50,25,75,65,85,95});
    Tree.remove(Tree.find(75));
    ASSERT_STREQ( "{50,25,85,65,95}", (Tree.preorder()).c_str() );
}

 
// Case 3. Scenario 3. Root Node.
// Node has right child that has left child.
TEST(BinaryTree, Delete_Root_With_Right_Child_With_Left_Child_Root){
    BinaryTree<int> Tree( std::vector<int> {50,25,75,15,35,65,85});
    Tree.remove(Tree.find(50));
    ASSERT_STREQ( "{65,25,15,35,75,85}", (Tree.preorder()).c_str() );
}

// Case 3. Scenario 3. Right Child.
//  Node has right child that has left child.
TEST(BinaryTree, Delete_Non_Terminal_Right_Child_With_Right_Child_With_Left_Child_Root){
    BinaryTree<int> Tree( std::vector<int> {50,25,75,65,85,60,70,80,90});
    Tree.remove(Tree.find(75));
    ASSERT_STREQ( "{50,25,80,65,60,70,85,90}", (Tree.preorder()).c_str() );
}

// Case 3. Scenario 3. Left Child.
//  Node has right child that has left child.
TEST(BinaryTree, Delete_Non_Terminal_Left_Child_With_Right_Child_With_Left_Child_Root){
    BinaryTree<int> Tree( std::vector<int> {50,25,15,35,10,20,30,40,75});
    Tree.remove(Tree.find(25));
    ASSERT_STREQ( "{50,30,15,10,20,35,40,75}", (Tree.preorder()).c_str() );
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv); 
  return RUN_ALL_TESTS();
}