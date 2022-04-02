CREATE TABLE tags
  (
     id   INT(6) UNSIGNED auto_increment PRIMARY KEY,
     name VARCHAR(30) NOT NULL,
     INDEX (name)
  );

CREATE TABLE documents
  (
     id   INT(6) UNSIGNED auto_increment PRIMARY KEY,
     name VARCHAR(30) NOT NULL,
     INDEX (name)
  );

CREATE TABLE tags_documents
  (
     id       INT(6) UNSIGNED auto_increment PRIMARY KEY,
     tag      INT(6) UNSIGNED NOT NULL,
     document INT(6) UNSIGNED NOT NULL,
     INDEX (tag, document)
  );

ALTER TABLE tags_documents
  ADD CONSTRAINT fk_tag FOREIGN KEY (tag) REFERENCES tags(id) ON DELETE RESTRICT
  ON UPDATE RESTRICT;

ALTER TABLE tags_documents
  ADD CONSTRAINT fk_document FOREIGN KEY (document) REFERENCES documents(id) ON
  DELETE RESTRICT ON UPDATE RESTRICT;
  
-- adding unique key to name column in <tags> table
CREATE UNIQUE INDEX tag_index ON tags (name);