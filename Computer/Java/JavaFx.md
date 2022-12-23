# 布局

`Hbox`:左右布局，

`vbox`:垂直排列，竖直向下

`Border Pane`:分成了上下左右中五个位置，好像所有软件基本都有这样的布局



# TreeView

` 找不到模块: javafx.controlsTreeView`里面的东西叫做`TreeItem`，然后设置下属节点的话就是`getChildren().add()`这样加入到`TreeView`里面

`看选择的是哪一个东西我们可以直接加监控器`

```java
// 这里TreeView的选择模型然后在被选择的属性里面加入监控器，监控器里面就可以直接加入新的监控器
treeView.getSelectionModel().selectedItemProperty().addListener(new ChangeListener<TreeItem<String>>()
        {
            @Override
            public void changed(ObservableValue<? extends TreeItem<String>> observable, TreeItem<String> oldValue, TreeItem<String> newValue)
            {
                if (newValue != null)
                {
                    System.out.println(newValue.getValue());
                }
            }
        });
```

# Table View

```java
// 这是一列，然后Name是这个名字是什么，下面的name是从Product里面获取name的值
TableColumn<Product, String> nameColumn = new TableColumn<>("Name");
nameColumn.setMinWidth(200);
nameColumn.setCellValueFactory(new PropertyValueFactory<>("name"));
```



## Table View 的删除

```java
private void deleteButtonClicked()
{
        ObservableList<Product> allProducts = tableView.getItems();
        ObservableList<Product> selectedProducts = tableView.getSelectionModel().getSelectedItems();
        selectedProducts.forEach(allProducts::remove);

}
```

# 菜单栏

`MenuBar`：就是菜单栏 找不到模块: javafx.controls

`Menu`：可以有列表，就是子列表

`MenuItem`:这才是一个小小的按钮

