package bgu.spl.net.srv;

import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentLinkedQueue;

public class BookClubDataBase {
        public static ConcurrentHashMap<String, BookClubMember> nameUserMap = new ConcurrentHashMap<String, BookClubMember>();
        public static ConcurrentHashMap<Integer, BookClubMember> idMemberMap = new ConcurrentHashMap<Integer, BookClubMember>();
        public static ConcurrentHashMap<String, ConcurrentLinkedQueue<BookClubMember>> genreMap = new ConcurrentHashMap<String, ConcurrentLinkedQueue<BookClubMember>>();


}


