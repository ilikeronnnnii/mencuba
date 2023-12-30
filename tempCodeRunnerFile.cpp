for (int i = 0; i < user.size(); i++)
    {
        userList.insertNodeUser(user[i].getName(), user[i].getIC(), user[i].getPhone(), user[i].getEmail());
    }
    userList.displayListUser();