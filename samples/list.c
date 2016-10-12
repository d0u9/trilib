#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "../list.h"

/*
 * Simple examples to illustrate how to use library of double-list.h
 * @version:	v0.2
 * @author:	Douglas Su
 * @date:	05/19/2015
 */

/*
 * In this example, we design a student score management system which is
 * implemented by a double-linked list.
 */

/*
 * Here, in the example, the double-linked list has an explicit node which
 * helps to manipulate the state of list. Some extra informations are stored
 * in the header, such as the amount of students, the highest and lowest
 * socres, etc.
 */
struct score_list {
	int amount_of_students;
	int highest_score;
	int lowest_score;
	struct list_head list;
};

/*
 * In the list, each node is represented by struct student in which stores
 * the name of student and corresponding score.
 * The list is embedded in each node as a member variable.
 */
struct student {
	char name[64];
	int score;
	struct list_head list;
};

int main(int argc, const char *argv[])
{
	/* Create and inilize a head node */
	struct score_list exam_score_a = {
		.amount_of_students = 0,
		.highest_score = 0,
		.lowest_score = 100,
		/* We initilized the list staticlly here */
		.list = LIST_HEAD_INIT(exam_score_a.list)
	};

	struct list_head *temp_list = NULL;
	struct student *temp_entry = NULL;

	/* Then, we create 5 nodes and insert them into the list */
	for (int i = 0; i < 6; ++i) {
		struct student *stdt =
		    (struct student *) malloc(sizeof (*stdt));

		sprintf(stdt->name, "student %d", i);
		stdt->score = 50 + i * 10;

		/* Inilize the list node */
		INIT_LIST_HEAD(&stdt->list);

		/* Insert the node into the list */
		list_add(&stdt->list, &exam_score_a.list);

		exam_score_a.amount_of_students++;
		exam_score_a.highest_score =
		    (exam_score_a.highest_score <
		     stdt->score) ? stdt->score : exam_score_a.highest_score;
		exam_score_a.lowest_score =
		    (exam_score_a.lowest_score >
		     stdt->score) ? stdt->score : exam_score_a.lowest_score;
	}

	/* interate each nodes by different methods and print them */
	printf("Iterate each nodes\n");
	printf("There is(are) %d student(s) in this list\n"
	       "Highest score is %d, lowest score is %d\n",
	       exam_score_a.amount_of_students,
	       exam_score_a.highest_score, exam_score_a.lowest_score);

	printf("\nIterate by list_for_each\n");
	list_for_each(temp_list, &exam_score_a.list) {
		struct student *temp_list_stdt =
		    list_entry(temp_list, struct student, list);
		printf("Student name: %s, score: %d\n", temp_list_stdt->name,
		       temp_list_stdt->score);
	}

	printf("\nIterate by list_for_each_entry\n");
	list_for_each_entry(temp_entry, &exam_score_a.list, list) {
		printf("Student name: %s, score: %d\n", temp_entry->name,
		       temp_entry->score);
	}

	printf("\nIterate by list_for_each_entry_reverse\n");
	list_for_each_entry_reverse(temp_entry, &exam_score_a.list, list) {
		struct student *temp_list_stdt =
		    list_entry(temp_list, struct student, list);
		printf("Student name: %s, score: %d\n", temp_list_stdt->name,
		       temp_list_stdt->score);
	}

	printf("\nIterate by list_for_each_entry_reverse\n");
	list_for_each_entry_reverse(temp_entry, &exam_score_a.list, list) {
		printf("Student name: %s, score: %d\n", temp_entry->name,
		       temp_entry->score);
	}

	/*
	 * Delete an entry
	 * We delete a node from exam_score_a.list.
	 */
	printf("\nDelete a node from exam_score_a\n");
	temp_list = exam_score_a.list.next;
	list_del_init(temp_list);

	printf("After deleting, the exam_score_a is:\n");
	list_for_each_entry(temp_entry, &exam_score_a.list, list) {
		printf("Student name: %s, score: %d\n", temp_entry->name,
		       temp_entry->score);
	}

	/*
	 * Move the list node which was deleted to exam_score_b
	 */
	/* Create and inilize another node */
	struct score_list exam_score_b = {
		.amount_of_students = 0,
		.highest_score = 0,
		.lowest_score = 100,
		/* We initilized the list staticlly here */
		.list = LIST_HEAD_INIT(exam_score_b.list)
	};

	printf("\nMove the node which we just deleted to exam_score_b\n");
	list_move(temp_list, &exam_score_b.list);

	printf("The exam_score_b after list_move is:\n");
	list_for_each_entry(temp_entry, &exam_score_b.list, list) {
		printf("Student name: %s, score: %d\n", temp_entry->name,
		       temp_entry->score);
	}

	/*
	 * Move the next node in exam_score_a after head to exam_score_b
	 */
	printf
	    ("\nMove the next node in exam_score_a after head to exam_score_b\n");
	list_move(exam_score_a.list.next, &exam_score_b.list);

	printf("After moving, exam_score_b:\n");
	list_for_each_entry(temp_entry, &exam_score_b.list, list) {
		printf("Student name: %s, score: %d\n", temp_entry->name,
		       temp_entry->score);
	}

	/*
	 * Move the next node in exam_score_a after head to exam_score_b
	 */
	printf("\nMove the next node in exam_score_a after head to tail of exam_score_b\n");
	list_move_tail(exam_score_a.list.next, &exam_score_b.list);

	printf("After moving, exam_score_b:\n");
	list_for_each_entry(temp_entry, &exam_score_b.list, list) {
		printf("Student name: %s, score: %d\n", temp_entry->name,
		       temp_entry->score);
	}

	printf ("Now the exam_score_a looks like:\n");
	list_for_each_entry(temp_entry, &exam_score_a.list, list) {
		printf("Student name: %s, score: %d\n", temp_entry->name,
		       temp_entry->score);
	}

	/*
	 * Splice all nodes in exam_score_a to exam_score_b after its head and
	 * then re-intailize it for reusing.
	 */
	printf("\nSplice exam_score_a to exam_score_b\n");
	list_splice_init(&exam_score_a.list, &exam_score_b.list);

	printf("Now, the exam_score_b looks like:\n");
	list_for_each_entry(temp_entry, &exam_score_b.list, list) {
		printf("Student name: %s, score: %d\n", temp_entry->name,
		       temp_entry->score);
	}

	printf("Now, the exam_score_a looks like:\n");
	list_for_each_entry(temp_entry, &exam_score_a.list, list) {
		printf("Student name: %s, score: %d\n", temp_entry->name,
		       temp_entry->score);
	}

	/*
	 * Splice all nodes in exam_score_b back to exam_score_b before its
	 * head and then re-intailize it for reusing.
	 */
	printf("\nSplice exam_score_b back to exam_score_a\n");
	list_splice_tail_init(&exam_score_b.list, &exam_score_a.list);

	printf("Now, the exam_score_b looks like:\n");
	list_for_each_entry(temp_entry, &exam_score_b.list, list) {
		printf("Student name: %s, score: %d\n", temp_entry->name,
		       temp_entry->score);
	}

	printf("Now, the exam_score_a looks like:\n");
	list_for_each_entry(temp_entry, &exam_score_a.list, list) {
		printf("Student name: %s, score: %d\n", temp_entry->name,
		       temp_entry->score);
	}
}
