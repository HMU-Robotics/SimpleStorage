drop database HMU_ROBOTICS_STORAGE;
create database HMU_ROBOTICS_STORAGE;
use HMU_ROBOTICS_STORAGE;

create table role(
    id int not null auto_increment,
    name text,
    primary key (id)
);

insert into role(name) values ("admin");
insert into role(name) values ("editor");
insert into role(name) values ("viewer");

create table user(
    id int not null auto_increment,
    username varchar(254) not null,
    email varchar(254) not null,
    first_name text not null,
    last_name text not null,
    password varchar(254),
    role_id int not null,
    primary key (id),
    foreign key (role_id) references role(id)
);

create table item(
    id int not null auto_increment,
    name text not null ,
    description text,
    code varchar(36) not null,
    status enum('available', 'unavailable') default 'available',
    created_at timestamp default current_timestamp,
    updated_at timestamp default current_timestamp on update current_timestamp,
    primary key (id)
);

create table reservation(
    id int not null auto_increment,
    user_id int not null,
    item_id int not null,
    start_data timestamp not null,
    end_data timestamp not null,
    create_at timestamp default current_timestamp,
    primary key (id),
    foreign key (user_id) references user(id),
    foreign key (user_id) references item(id)
);