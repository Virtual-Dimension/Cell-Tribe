echo 设置用户信息

set/p a1=请输入名称：

git config --global user.name %a1%

set/p a2=请输入邮箱：

git config --global user.email %a2%

pause